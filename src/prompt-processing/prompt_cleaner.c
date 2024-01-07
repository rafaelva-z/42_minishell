/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:18:31 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/07 15:11:35 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
char	*prompt_cleaner(const char *prompt)
{
	char	*trim;
	char	*new_prompt;

	if (!prompt)
		return (NULL);
	new_prompt = space_trim(prompt);
	if (!new_prompt)
		return (NULL);
	trim = ft_strtrim(new_prompt, " \t");
	if (!trim)
	{
		free(new_prompt);
		perror("MEMORY ERROR");
		exit(-1000);
	}
	free(new_prompt);
	return (trim);
}
