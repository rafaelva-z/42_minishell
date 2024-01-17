/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:18:31 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/17 20:15:08 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	space_trim_loop(const char *prompt, char *tmp, int *i, int *j)
{
	char	c;

	while (prompt[*i] && prompt[*i] != '\"' && prompt[*i] != '\''
		&& !ft_isspace(prompt[*i]))
		tmp[(*j)++] = prompt[(*i)++];
	if (prompt[*i] == '\'' || prompt[*i] == '\"')
	{
		c = prompt[*i];
		tmp[(*j)++] = prompt[(*i)++];
		while (prompt[*i] && prompt[*i] != c)
			tmp[(*j)++] = prompt[(*i)++];
		tmp[(*j)++] = prompt[(*i)++];
	}
	if (prompt[*i] && ft_isspace(prompt[*i]))
		tmp[(*j)++] = ' ';
	while (prompt[*i] && ft_isspace(prompt[*i]))
		(*i)++;
}

/**
 * @brief	removes extra spaces between arguments leaving only one where
 * 			there are more than one, leaving the spaces inside " or ' intact
*/
static char	*space_trim(const char *prompt)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(ft_strlen(prompt) + 1, 1);
	if (!tmp)
		free_and_exit(NULL, "minishell: memory alocation failed",
			ES_ALLOC_FAIL, 0);
	while (prompt[i])
		space_trim_loop(prompt, tmp, &i, &j);
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
			ES_ALLOC_FAIL, 0);
	*prompt = trim;
	return (0);
}
