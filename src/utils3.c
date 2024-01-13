/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:25:48 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/13 18:20:06 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 *	@brief	Returns the amount of pipe redirections on the given string.
 *			If the prompt is not valid the returned value can be wrong!
*/
int	get_pipe_count(char *str)
{
	int	pipe_count;
	int	i;

	pipe_count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '|' && !is_inside_quotes(str, i))
		{
			if (str[i + 1] == '|')
				i += 2;
			else
				i++;
			pipe_count++;
		}
		if (str[i])
			i++;
	}
	return (pipe_count);
}

int	count_commands(char **tokens, size_t pipe)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!tokens || !*tokens)
		return (0);
	while (pipe && tokens[i])
	{
		if (tokens[i][0] == RDIR_PIPE)
			pipe--;
		i++;
	}
	while (tokens[i] && tokens[i][0] != RDIR_PIPE)
	{
		if (is_redir_val(tokens[i][0]) && tokens[i][0] != RDIR_PIPE)
			i++;
		else if (!is_redir_val(tokens[i][0]))
			count++;
		i++;
	}
	return (count);
}

int	count_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}
