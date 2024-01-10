/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_add_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:32:48 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/10 21:32:57 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	space_toadd_count_helper(char *prompt, int *i, int *space_count)
{
	if (what_redir(&prompt[*i]) == RDIR_APP
		|| what_redir(&prompt[*i]) == RDIR_HDOC)
	{
		if (!prompt[*i] || !prompt[(*i) + 2])
			return ;
		if (prompt[(*i) + 2] != ' ')
			(*space_count)++;
		if (*i != 0 && prompt[(*i) - 1] != ' ')
			(*space_count)++;
		(*i)++;
	}
	else
	{
		if (!prompt[*i] || !prompt[(*i) + 1])
			return ;
		if (prompt[(*i) + 1] != ' ')
			(*space_count)++;
		if (*i != 0 && prompt[(*i) - 1] != ' ')
			(*space_count)++;
	}
	(*i)++;
}

/**
 * @brief	counts how many spaces are to be added, in order to allocate
 * 			the correct amount of memory on add_spaces_redirections
*/
static int	space_toadd_count(char *prompt)
{
	int	i;
	int	space_count;

	i = 0;
	space_count = 0;
	while (prompt[i])
	{
		while (prompt[i] && (!is_redir(prompt[i])
				|| is_inside_quotes(prompt, i)))
			i++;
		space_toadd_count_helper(prompt, &i, &space_count);
	}
	return (space_count);
}

/**
 * @brief	This function was made to make add_spaces_redirections shorter
 * 			(norminette)
*/
static void	add_spaces_redirections_loop(char **prompt,
				char **new_prompt, int *i, int *j)
{
	while ((*prompt)[*i])
	{
		while ((*prompt)[*i] && ((!is_redir((*prompt)[*i])
				|| is_inside_quotes(*prompt, *i))))
			(*new_prompt)[(*j)++] = (*prompt)[(*i)++];
		if (!(*prompt)[*i])
			break ;
		if (*j != 0 && (*new_prompt)[*j - 1] != ' ')
			(*new_prompt)[(*j)++] = ' ';
		if (what_redir(&(*prompt)[*i]) == RDIR_APP
			|| what_redir(&(*prompt)[*i]) == RDIR_HDOC)
		{
			(*new_prompt)[(*j)++] = (*prompt)[(*i)++];
			(*new_prompt)[(*j)++] = (*prompt)[(*i)++];
		}
		else
			(*new_prompt)[(*j)++] = (*prompt)[(*i)++];
		if ((*prompt)[*i] != ' ')
			(*new_prompt)[(*j)++] = ' ';
	}
}

/**
 * @brief	adds a space between redirections and other words if there isn't one
*/
void	add_spaces_redirections(char **prompt)
{
	int		space_count;
	int		i;
	int		j;
	char	*new_prompt;

	space_count = space_toadd_count(*prompt);
	if (space_count == 0)
		return ;
	i = 0;
	j = 0;
	new_prompt = malloc(ft_strlen(*prompt) + space_count + 1);
	if (!new_prompt)
		free_and_exit(NULL, "minishell: memory alocation failed", ES_ALLOC_FAIL);
	add_spaces_redirections_loop(prompt, &new_prompt, &i, &j);
	new_prompt[j] = '\0';
	free(*prompt);
	*prompt = new_prompt;
}
