/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:18:31 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/11 12:46:47 by rvaz             ###   ########.fr       */
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
		free_and_exit(NULL, "minishell: memory alocation failed",
			ES_ALLOC_FAIL);
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
int	prompt_cleaner(char **prompt)
{
	char	*trim;
	char	*spc_trim;

	if (!*prompt)
		return (-1);
	spc_trim = space_trim(*prompt);
	trim = ft_strtrim(spc_trim, " \t");
	free(spc_trim);
	free(*prompt);
	if (!trim)
		free_and_exit(NULL, "minishell: memory alocation failed",
			ES_ALLOC_FAIL);
	*prompt = trim;
	return (0);
}
