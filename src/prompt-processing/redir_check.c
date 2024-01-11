/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 03:02:07 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/11 12:51:04 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *	@brief	checks on the given string what is the next character type ignoring
 *			spaces.
 *	@return	0 if the next character is alphanumeric or a symbol, a positive number if the next
 *			character is a redirection, -1 if the next character is a NULL character
*/
static int	check_after_redir(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (is_redir(*str))
		return (what_redir(str));
	else if (*str == '\0')
		return (-1);
	return (0);
}

/**
 *	@brief	check for synthax errors about redirections
*/
int	redirection_check(char *prompt)
{
	int	redir_type;
	int	after_redir_type;
	int	i;

	i = 0;
	if (prompt[i] == '|')
		return (-1);
	while (prompt[i])
	{
		while (prompt[i] && !is_redir(prompt[i]))
			i++;
		if (prompt[i] && is_redir(prompt[i]) && !is_inside_quotes(prompt, i))
		{
			redir_type = what_redir(&prompt[i]);
			if (redir_type == RDIR_DPIPE) // double pipe
				return (-1);
			else if (redir_type == RDIR_APP || redir_type == RDIR_HDOC || redir_type == RDIR_DPIPE)
				i += 2;
			else if (redir_type == RDIR_IN || redir_type == RDIR_OUT || redir_type == RDIR_PIPE)
				i++;
			after_redir_type = check_after_redir(&prompt[i]);
			if (after_redir_type < 0 && redir_type != RDIR_PIPE && redir_type != RDIR_DPIPE) // found a non pipe redirect
			{
				if (redir_type == RDIR_PIPE)
					continue ;
				else
					return (-1);
			}
			else if (after_redir_type == -1 || after_redir_type == RDIR_PIPE || after_redir_type == RDIR_DPIPE) // found a '\0' || found a pipe redirect
				return (-1);
		}
		if (prompt[i])
			i++;
	}
	return (0);
}
