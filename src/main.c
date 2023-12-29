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

void	builtin_execute(char *prompt)
{
	if (ft_strncmp(prompt, "exit", 4) == 0)
		exit_shell(0);
	else if (ft_strncmp(prompt, "env", 3) == 0)
		print_env();
	else if (ft_strncmp(prompt, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(prompt, "cd", 2) == 0)
	{
		if (ft_strlen(prompt) > 2)
			cd(prompt + 3);
		else
			cd(NULL);
	}
	else if (ft_strncmp(prompt, "echo", 4) == 0)
		echo("");
	else if (ft_strncmp(prompt, "export", 6) == 0)
	{
		if (ft_strlen(prompt) > 6)
			export(prompt + 7);
		else
			export(NULL);
	}
	else if (ft_strncmp(prompt, "unset ", 5) == 0)
		unset(prompt + 6);
}

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

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*cursor;

	(void)argv;
	if (argc != 1)
		exit(0);
	prompt = NULL;
	cursor = NULL;
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
			if (quote_check(prompt))
			{
				printf("error: quotes open\n"); // Error
				free(prompt);
				continue ;
			}
			char *clean_prompt = prompt_cleaner(prompt);
			if (redirection_check(clean_prompt))
			{
				printf("error: redirect error");
				free(prompt);
				free(clean_prompt);
				continue ;
			}
			builtin_execute(clean_prompt); // temporary
			//	char **tokens = Tokenizer(clean_prompt)
			//	convert tokens to linked list
			//	Executer
			free(prompt);
			free(clean_prompt);
		}
	} 
	printf("exit\n");
	destroy_env();
	free(cursor);
	rl_clear_history();	//is this needed?
	exit(0);
}
