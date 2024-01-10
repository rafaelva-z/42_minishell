/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scosta-j <scosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:33:14 by scosta-j          #+#    #+#             */
/*   Updated: 2023/09/07 15:33:14 by scosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal;

/**
 * @brief	Allocates the prompt cursor to param "char **cursor".
 * 			the cursor will be the username + the constant CURSOR
 * 			or just the constant CURSOR if there is no USER variable
*/
static void	get_prompt_cursor(void)
{
	t_envp	*shell;

	shell = get_env_struct();
	if (shell->cursor)
		free(shell->cursor);
	if (get_env_var("USER"))
	{
		shell->cursor = get_env_var("USER")->content + 5;
		shell->cursor = ft_strjoin(shell->cursor, CURSOR);
	}
}

//	TEST
// static void	print_commands_redirects(t_commands *commands)
// {
// 	printf("\n_________________\nREDIRECTIONS\n");
// 	t_commands		*test_c = commands;
// 	t_redirection	*test_r;
// 	while (test_c)
// 	{
// 		test_r = test_c->redirects;
// 		while (test_r)
// 		{
// 			printf("__type: %d\n", test_r->type);
// 			printf("__key_wrd: %s\n", test_r->key_wrd);
// 			test_r = test_r->next;
// 		}
// 		test_c = test_c->next;
// 		if (test_c)
// 			printf("-|PIPE|-\n");
// 	}
// 	printf("\n_________________\nCOMMANDS\n");
// 	test_c = commands;
// 	while (test_c)
// 	{
// 		int	f = 0;
// 		while (test_c->cmds[f])
// 		{
// 			printf("cmd: %s\n", test_c->cmds[f]);
// 			f++;
// 		}
// 		test_c = test_c->next;
// 		if (test_c)
// 			printf("-|PIPE|-\n");
// 	}
// }

int	prompt_processing(char **prompt)
{
	if (quote_check(*prompt))
	{
		free(*prompt);
		display_error(ERR_QUOTES);
		get_env_struct()->exit_status = ES_OP_N_PERM;
		return (-1);
	}
	prompt_cleaner(prompt);
	if (redirection_check(*prompt))
	{
		free(*prompt);
		display_error(ERR_RDIR);
		get_env_struct()->exit_status = ES_OP_N_PERM;
		return (-2);
	}
	add_spaces_redirections(prompt);
	return (0);
}

static void	get_prompt(char **prompt)
{
	t_envp *shell;

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
	t_envp *shell;

	shell = get_env_struct();
	shell->commands = get_command_linkedlst(*prompt);
	shell->tokens = tokenizer(*prompt);
	free(*prompt);
	add_redirections(&shell->commands, shell->tokens);
	add_commands(&shell->commands, shell->tokens);
}

static void	shell_loop()
{
	t_envp	*shell;
	char	*prompt;

	shell = get_env_struct();
	while (1)
	{
		get_prompt(&prompt);
		if (!prompt)
			break ;
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
