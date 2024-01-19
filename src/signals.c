/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:56:23 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/19 14:16:44 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/types.h>
#include <signal.h>

/**
 * 	CTRL + C = SIGINT
 * 	CTRL + \ = SIGQUIT
 * 	CTRL + D = EOF (char)(-1)
*/

/**
 * @brief signal handler for while waiting for prompt on the main function
*/
static void	sighandler_main(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 0;
		get_env_struct()->exit_status = ES_SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

/**
 * @brief signal handler for while inside heredoc child process
*/
static void	sighandler_child_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		close(STDIN_FILENO);
	}
}

/**
 * @brief signal handler for while inside the loop function in the main function
*/
static void	sighandler_loop(int signal)
{
	t_envp	*shell;

	shell = get_env_struct();
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		shell->exit_status = ES_SIGINT;
	}
	else if (signal == SIGQUIT)
	{
		g_signal = SIGQUIT;
		shell->exit_status = ES_SIGQUIT;
	}
}

/**
 * @brief defines signal behaviour
*/
void	set_signals(int process)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;
	sigset_t			block_mask;

	(void)block_mask;
	sigemptyset(&sig_int.sa_mask);
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = SIG_IGN;
	if (process == HNDLR_MAIN)
	{
		g_signal = 0;
		sig_int.sa_handler = sighandler_main;
	}
	else if (process == HNDLR_CHILD_HD)
		sig_int.sa_handler = sighandler_child_heredoc;
	else if (process == HNDLR_LOOP)
	{
		sig_quit.sa_handler = sighandler_loop;
		sig_int.sa_handler = sighandler_loop;
	}
	sig_int.sa_flags = 0;
	sig_quit.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
