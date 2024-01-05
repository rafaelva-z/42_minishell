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

/**
 * @brief	Allocates the prompt cursor to param "char **cursor".
 * 			the cursor will be the username + the constant CURSOR
 * 			or just the constant CURSOR if there is no USER variable
*/
void	get_prompt_cursor(char **cursor)
{
	if (*cursor)
		free(*cursor);
	if (get_env_var("USER"))
	{
		*cursor = get_env_var("USER")->content + 5;
		*cursor = ft_strjoin(*cursor, CURSOR);
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
	char	*new_prompt;
	char	*final_prompt;

	if (quote_check(*prompt))
	{
		perror("error: quotes open\n"); // Error
		free(*prompt);
		*prompt = NULL;
		return (1);
	}
	new_prompt = prompt_cleaner(*prompt);
	if (!new_prompt)
	{
		perror("error: prompt cleaner error\n"); // Error
		free(*prompt);
		*prompt = NULL;
		return (1);
	}
	if (redirection_check(new_prompt))
	{
		perror("error: redirect error");
		free(*prompt);
		*prompt = NULL;
		free(new_prompt);
		return (1);
	}
	final_prompt = add_spaces_redirections(new_prompt);
	if (!final_prompt)
	{
		perror("error: space redirections error");
		free(*prompt);
		*prompt = NULL;
		free(new_prompt);
		return (1);
	}
	if (final_prompt != new_prompt)
	{
		free(*prompt);
		free(new_prompt);
		*prompt = final_prompt;
		return (0);
	}
	free(new_prompt);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*prompt;
	char		*cursor;
	t_commands	*commands;
	char		**tokens;

	(void)argv;
	if (argc != 1)
		exit(0);
	prompt = NULL;
	cursor = NULL;
	commands = NULL;
	init_env(envp);
	get_prompt_cursor(&cursor);
	while (1)
	{
		set_signals();
		if (cursor)
			prompt = readline(cursor);
		else
			prompt = readline(CURSOR);
		if (prompt && *prompt)
			add_history(prompt);
		if (!prompt)
			break ;
		else
		{
			commands = NULL; //testing
			tokens = NULL; //testing
			get_env_struct()->first_cmd_struct = NULL; //testing
			prompt_processing(&prompt);
			if (!prompt)
			{
				printf("error: prompt processing error\n"); // Error
				break ;
			}
			commands = get_command_linkedlst(prompt);
			tokens = tokenizer(prompt);
			if (prompt)
				free(prompt);
			add_redirections(&commands, tokens);
			add_commands(&commands, tokens);
			//print_commands_redirects(commands);
			here_doc_manager();
			process_generator();
			// free (tokens);
			// free (commands->redirections)
			// free (commands);
		}
	}
	printf("exit\n");
	destroy_env();
	free(cursor);
	rl_clear_history();	//is this needed?
	exit(0);
}
