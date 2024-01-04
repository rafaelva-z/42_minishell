/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:55:32 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/04 13:16:50 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 *	@brief	checks if the given char is a redirection
*/
int	is_redir(char c)
{
	if (c && (c == '>' || c == '<' || c == '|'))
		return (1);
	return (0);
}

int	is_redir_val(char c)
{
	if (c && (c == RDIR_OUT || c == RDIR_IN || c == RDIR_PIPE
			|| c == RDIR_HDOC || c == RDIR_APP || c == RDIR_DPIPE))
		return (1);
	return (0);
}

/**
 *	@brief	checks if the given prompt contains redirections
*/
int	hasredir(char *prompt)
{
	while (prompt)
	{
		if (is_redir(*prompt))
			return (1);
		prompt++;
	}
	return (0);
}

/**
 *	@brief	returns the type of the given redirection
*/
int	what_redir(char *str)
{
	if (str && *str && is_redir(*str))
	{
		if (str[0] != str[1])
		{
			if (*str == '<')
				return (RDIR_IN);
			else if (*str == '>')
				return (RDIR_OUT);
			else if (*str == '|')
				return (RDIR_PIPE);
		}
		else
		{
			if (*str == '<')
				return (RDIR_HDOC);
			else if (*str == '>')
				return (RDIR_APP);
			else if (*str == '|')
				return (RDIR_DPIPE);
		}
	}
	return (0);
}
