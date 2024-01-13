/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 03:02:07 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/13 18:45:24 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *	@brief	checks on the given string what is the next character type ignoring
 *			spaces.
 *	@return	0 if the next character is alphanumeric or a symbol,
 *			a positive number if the next character is a redirection,
 *			-1 if the next character is a NULL character
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

static int	skip_redirection(int redir_type, int *i)
{
	if (redir_type == RDIR_DPIPE)
		return (-1);
	else if (redir_type == RDIR_APP
		|| redir_type == RDIR_HDOC
		|| redir_type == RDIR_DPIPE)
		(*i) += 2;
	else if (redir_type == RDIR_IN
		|| redir_type == RDIR_OUT
		|| redir_type == RDIR_PIPE)
		(*i)++;
	return (0);
}

static int	rdir_loop_error_cases(int after_redir_type, int redir_type)
{
	if (after_redir_type < -1 && after_redir_type 
		!= RDIR_PIPE && after_redir_type != RDIR_DPIPE)
	{
		if (redir_type == RDIR_PIPE)
			return (1);
		else
			return (-1);
	}
	else if (redir_type == RDIR_PIPE && after_redir_type == -1)
		return (-1);
	else if (after_redir_type == -1 || after_redir_type == RDIR_PIPE
		|| after_redir_type == RDIR_DPIPE)
		return (-1);
	return (0);
}

static int	redirection_check_loop(char *prompt, int *i)
{
	int	after_redir_type;
	int	redir_type;
	int	flag;

	flag = 0;
	while (prompt[*i] && !is_redir(prompt[*i]))
		(*i)++;
	if (prompt[*i] && is_redir(prompt[*i]) && !is_inside_quotes(prompt, *i))
	{
		redir_type = what_redir(&prompt[*i]);
		if (skip_redirection(redir_type, i) == -1)
			return (-1);
		after_redir_type = check_after_redir(&prompt[*i]);
		flag = rdir_loop_error_cases(after_redir_type, redir_type);
		if (flag)
			return (flag);
	}
	return (0);
}

/**
 *	@brief	check for synthax errors about redirections
*/
int	redirection_check(char *prompt)
{
	int	i;
	int	a;

	i = 0;
	if (prompt[i] == '|')
		return (-1);
	while (prompt[i])
	{
		a = redirection_check_loop(prompt, &i);
		if (a == -1)
			return (-1);
		else if (a == 1)
			continue ;
		if (prompt[i])
			i++;
	}
	return (0);
}
