/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:18:31 by rvaz              #+#    #+#             */
/*   Updated: 2023/12/04 21:31:50 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/**
 *	@brief checks if there are any quotations left unclosed
 *	@return (0) no quotes left open, (1) open single quote, (2) open double quote
 * 
*/
int	quote_check(const char *str)
{
	int		i;
	bool	dquote;
	bool	squote;

	i = -1;
	dquote = 0;
	squote = 0;
	while (str[++i])
	{
		if (!squote && !dquote)
		{
			if (str[i] == '\"')
				dquote = !dquote;
			else if (str[i] == '\'')
				squote = !squote;
			continue ;	
		}
		if (squote && str[i] == '\'') //USE TYPEDEF INSTEAD OF CHARACTERS
			squote = !squote;
		if (dquote && str[i] == '\"')
			dquote = !dquote;
	}
	return (squote + (dquote * 2));
}

/**
 * @brief	removes extra spaces between arguments leaving only one where
 * 			there are more than one, leaving the spaces inside " or ' intact
*/
char	*space_trim(const char *prompt)
{
	int	i;
	int	j;
	char *tmp;
	
	i = 0;
	j = 0;
	tmp = ft_calloc(ft_strlen(prompt) + 1, 1);
	while (prompt[i])
	{
		while (prompt[i] && prompt[i] != '\"' && prompt[i] != '\'' 
				&& prompt[i] != ' ')
			tmp[j++] = prompt[i++];
		if (prompt[i] && prompt[i] == '\"')
		{
			tmp[j++] = prompt[i++];
			while (prompt[i] && prompt[i] != '\"')
				tmp[j++] = prompt[i++];
		}
		else if (prompt[i] && prompt[i] == '\'') //USE TYPEDEF INSTEAD OF CHARACTERS
		{
			tmp[j++] = prompt[i++];
			while (prompt[i] && prompt[i] != '\'')
				tmp[j++] = prompt[i++];
		}
		if (prompt[i] && (prompt[i] == '\"' || prompt[i] == '\'' 
				|| prompt[i] == ' '))
			tmp[j++] = prompt[i++];
		while (prompt[i] && prompt[i] == ' ')
			i++;
	}
	tmp[j] = '\0';
	printf("%s\n", tmp);
	return (tmp);
}
/*
if (prompt[i])
	if (prompt[i] =='\''  || prompt[i] == '\"')
	{
		char c = prompt[i];   // FIX THIS TO MAKE IT SHORTER
		tmp[j++] = prompt[i++];
		while (prompt[i] && prompt[i] != c)
			tmp[j++] = prompt[i++];
	}

*/

int	prompt_reader(const char *prompt)
{
	char *trim;
	char *new_prompt;
	t_prompt *prompt_list;

	if (!prompt)
		return (0);
	(void)prompt_list;
	if (quote_check(prompt))
	{
		printf("error: quotes open"); // Error
		return (-1);
	}
	trim = ft_strtrim(prompt, " ");
	new_prompt = space_trim(trim); 
	//split_prompt(new_prompt);
	if (trim)
		free(trim);
	if (new_prompt)
		free(new_prompt);
	return (0);
}

// TODAYS WORK

// void	split_prompt(char *prompt)
// {

// }

// HEREDOC execution has priority over other redirections

//expand // "$PWD" becomes ./path

