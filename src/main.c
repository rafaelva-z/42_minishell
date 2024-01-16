/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 01:38:40 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/11 01:38:40 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal;

/*
static void	print_commands_redirects(t_commands *commands)
{
	printf("\n\n\n_________________\nREDIRECTIONS\n");
	t_commands		*test_c = commands;
	t_redirection	*test_r;
	while (test_c)
	{
		test_r = test_c->redirects;
		while (test_r)
		{
			printf("__type: %d\n", test_r->type);
			printf("__key_wrd: %s\n", test_r->key_wrd);
			test_r = test_r->next;
		}
		test_c = test_c->next;
		if (test_c)
			printf("-|PIPE|-\n");
	}
	printf("\n_________________\nCOMMANDS\n");
	test_c = commands;
	while (test_c)
	{
		int	f = 0;
		while (test_c->cmds[f])
		{
			printf("cmd: %s\n", test_c->cmds[f]);
			f++;
		}
		test_c = test_c->next;
		if (test_c)
			printf("-|PIPE|-\n");
	}
}
*/

/**
 * @brief	get a prompt from stdin into 'prompt' and add it to history
*/
static void	get_prompt(char **prompt)
{
	t_envp	*shell;

	shell = get_env_struct();
	set_signals(HNDLR_MAIN);
	if (shell->cursor)
		*prompt = readline(shell->cursor);
	else
		*prompt = readline(CURSOR);
	if (*prompt && **prompt)
		add_history(*prompt);
}

static void	create_commands_and_redirections_struct(char **prompt)
{
	t_envp	*shell;

	shell = get_env_struct();
	shell->commands = get_command_linkedlst(*prompt);
	shell->tokens = tokenizer(*prompt);
	free(*prompt);
	add_redirections(&shell->commands, shell->tokens);
	add_commands(&shell->commands, shell->tokens);
}

static void	shell_loop_start(char **prompt)
{
	set_env_var("_", "/usr/bin/env");
	if (g_signal == SIGINT)
		write(1, "\n", 1);
	set_signals(HNDLR_MAIN);
	get_prompt(prompt);
}

static void	shell_loop(void)
{
	char			*prompt;

	while (true)
	{
		shell_loop_start(&prompt);
		if (!prompt)
			free_and_exit(NULL, ft_strdup(MSG_EXIT), STDOUT_FILENO);
		else
		{
			set_signals(HNDLR_LOOP);
			if (!*prompt)
			{
				free(prompt);
				continue ;
			}
			if (prompt_processing(&prompt))
				continue ;
			expansion_manager(&prompt);
			create_commands_and_redirections_struct(&prompt);
			here_doc_manager();
			process_generator();
			free_matrix_and_commands();
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		exit(0);
	init_env(envp);
	get_prompt_cursor();
	set_shlvl();
	shell_loop();
	free_and_exit(NULL, NULL, 0);
}
