/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:27:31 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/13 16:43:26 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	here_doc_loop(t_redirection *rdir, int fd[2])
{
	char			*s;
	int				len;

	len = ft_strlen(rdir->key_wrd);
	while (1)
	{
		s = readline(">");
		if (!s || g_signal == SIGINT || (ft_strncmp(rdir->key_wrd, s, len)
				== 0 && len == (int)(ft_strlen(s))))
			break ;
		expansion_manager(&s);
		write(fd[1], s, ft_strlen(s));
		write(fd[1], "\n", 1);
		free (s);
	}
	if (s)
		free (s);
	else
		ft_putstr_fd(MSG_HDOC_EOF, STDOUT_FILENO);
}

/**
*	@brief The name says it all: simulates a here_doc. It does it by reading from
*	the standard input, within the command itself and the limiter word.
*/
void	here_doc(t_redirection *rdir, int fd[2])
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	set_signals(HNDLR_CHILD_HD);
	rl_cleanup_after_signal();
	here_doc_loop(rdir, fd);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	close(fd[0]);
	close(fd[1]);
	free_and_exit(NULL, NULL, 0);
}

/*
* @brief Checks if theres any here_doc in the redirections of each command
* and executes them, in case of it's existence.
*/
static void	here_doc_check(t_commands *commands)
{
	int				fd[2];
	pid_t			pid;
	t_redirection	*redir;

	redir = commands->redirects;
	while (redir && g_signal == 0)
	{
		if (redir->type != RDIR_HDOC)
		{
			redir = redir->next;
			continue ;
		}
		to_close(commands->hd_fd);
		if (pipe(fd) == -1)
			free_and_exit(NULL, ft_strdup("Pipe error\n"), ES_PIPE);
		pid = fork();
		if (pid == 0)
			here_doc(redir, fd);
		waitpid(pid, NULL, 0);
		fd[1] = to_close(fd[1]);
		commands->hd_fd = fd[0];
		redir = redir->next;
	}
}

/*
* @brief Manages all here_docs
*/
void	here_doc_manager(void)
{
	t_commands		*current;
	struct termios	term;

	current = get_env_struct()->commands;
	tcgetattr(STDIN_FILENO, &term);
	while (current && g_signal == 0)
	{
		if (current->redirects)
		{
			here_doc_check(current);
			tcsetattr(STDIN_FILENO, TCSANOW, &term);
		}
		current = current->next;
	}
}
