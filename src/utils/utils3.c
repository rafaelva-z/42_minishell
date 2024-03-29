/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:25:48 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/19 15:52:35 by rvaz             ###   ########.fr       */
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

/**
 * @brief	Counts the amount of commands (non-redirections) until
 * 			the next RDIR_PIPE or NULL character.
*/
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

/**
 * @brief	Counts the amount of strings in given the matrix.
*/
int	count_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void	*safe_malloc(int bytes)
{
	void	*alloc;

	alloc = malloc(bytes);
	if (!alloc)
		free_and_exit(NULL, ERR_ALLOC, ES_ALLOC_FAIL, 0);
	return (alloc);
}

char	*get_var_name(char *var)
{
	int		i;
	int		j;
	char	*new_var;

	if (!var)
		return (NULL);
	i = 0;
	j = -1;
	while (var[i] && var[i] != '=')
		i++;
	new_var = safe_malloc(i + 1);
	while (++j < i)
		new_var[j] = var[j];
	new_var[j] = '\0';
	return (new_var);
}
