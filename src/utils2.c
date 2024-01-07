/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:41:58 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/07 01:03:17 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
*	@brief closes an fd in a safe way
*	@param (fd)
*	@returns -1, so it can be associated to the fd variable that was closed
*/
int	to_close(int fd)
{
	if (fd > 2)
		close(fd);
	return (-1);
}

/**
*	@brief checks if a token is a redirection
*	@param the first char of a token
*	@returns 1 if its a redirection and 0 if it isn't
*/
static int	is_redir_token(char c)
{
	if (c && (c == '>' * -1 || c == '<' * -1 || c == '|' * -1))
		return (1);
	return (0);
}

/**
*	@brief sets a token as a redirection
*	@param str the toke
*	@returns the redirection value if str represents one
*	and the first char of str if it isnt a redirectrion
*/
int	what_redir_token(char *str)
{
	if (str && *str && is_redir_token(*str))
	{
		if (str[0] != str[1])
		{
			if (*str == '<' * -1)
				return (RDIR_IN);
			else if (*str == '>' * -1)
				return (RDIR_OUT);
			else if (*str == '|' * -1)
				return (RDIR_PIPE);
		}
		else
		{
			if (*str == '<' * -1)
				return (RDIR_HDOC);
			else if (*str == '>' * -1)
				return (RDIR_APP);
			else if (*str == '|' * -1)
				return (RDIR_DPIPE);
		}
	}
	return (str[0]);
}
/**
 *	@brief Sets the SHLVL enviroment variable to the apropriate value
 *	contains non-numbr				shlvl = 1
 *	not set							shlvl = 1
 *	int btween 0 & 2147483645		shlvl = int++
 *	numbers like 0000005			shlvl = 6 (5++)
 *	negative int					shlvl = 0
 *	999 to 2147483646				shlvl = 1 + error message
 *	bash: warning: shell level (2147483647) too high, resetting to 1
 *	bigger than 2147483646			shlvl = 0
*/
void	set_shlvl()
{
	// long int		i;		set but not used
	int		shlvl;
	char	*shlvl_val;
	
	// i = 0;
	shlvl_val = get_env_var_value("SHLVL");
	if (shlvl_val && contains_only_nbr(shlvl_val))
	{
		shlvl = ft_atoi(shlvl_val);
		if (shlvl >= 999 && shlvl <= 2147483646)
			perror("warning: shell level (insert value here) too high, resetting to 1"); // Join
		else if (shlvl < 0 || shlvl > 2147483646)
		{
			set_env_var("SHLVL", "0");
			return ;
		}
		else if (shlvl > 0 && shlvl < 999)
		{
			set_env_var("SHLVL", ft_itoa(++shlvl));
			return ;
		}
	}
	set_env_var("SHLVL", "1");
}

