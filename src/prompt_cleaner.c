/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:18:31 by rvaz              #+#    #+#             */
/*   Updated: 2023/12/28 19:23:57 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/**
 *	@brief checks if there are any quotations left unclosed
 *	@return (0) no quotes left open, (1) open single quote, (2) open double quote
*/
int	quote_check(const char *str)
{
	char	c;

	c = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (!c)
		{
			if (*str == SQUOTE || *str == DQUOTE)
				c = *str;
		}
		else if (c == *str)
			c = 0;
		str++;
	}
	return ((c == SQUOTE) + ((c == DQUOTE) * 2));
}

/**
 * @brief	removes extra spaces between arguments leaving only one where
 * 			there are more than one, leaving the spaces inside " or ' intact
*/
static char	*space_trim(const char *prompt)
{
	int		i;
	int		j;
	char	c;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(ft_strlen(prompt) + 1, 1);
	if (!tmp)
		return (NULL);
	while (prompt[i])
	{
		while (prompt[i] && prompt[i] != DQUOTE && prompt[i] != SQUOTE
			&& !ft_isspace(prompt[i]))
			tmp[j++] = prompt[i++];
		if (prompt[i] == SQUOTE || prompt[i] == DQUOTE)
		{
			c = prompt[i];
			tmp[j++] = prompt[i++];
			while (prompt[i] && prompt[i] != c)
				tmp[j++] = prompt[i++];
			tmp[j++] = prompt[i++];
		}
		if (prompt[i] && ft_isspace(prompt[i]))
			tmp[j++] = ' ';
		while (prompt[i] && ft_isspace(prompt[i]))
			i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

/**
 * @brief	uses space_trim and ft_strtrim to clean the prompt form extra spaces
*/
char *prompt_cleaner(const char *prompt)
{
	char	*trim;
	char	*new_prompt;

	if (!prompt)
		return (NULL);
	trim = ft_strtrim(prompt, " "); // maybe switch trim to after space_trim, because there may be a space in the end after space_trim
	if (!trim)
		return (NULL);
	new_prompt = space_trim(trim);
	if (!new_prompt)
	{
		free(trim);
		return (NULL);
	}
	free(trim);
	return (new_prompt);
}
