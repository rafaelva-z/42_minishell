/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:28:39 by rvaz              #+#    #+#             */
/*   Updated: 2023/09/21 14:00:54 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief unsets the env variable given
 * @param name the variable to unset
 * @example unset_env_var("PATH");
*/
static void	unset_env_var(const char *name)
{
	t_envp		*shell;
	t_env_var	*current;

	shell = get_env_struct();
	if (!name || !shell->vars)
		return ;
	current = shell->get(name);
	if (!current)
		return ;
	if (current->previous)
		current->previous->next = current->next;
	if (current->next)
		current->next->previous = current->previous;
	ft_lstdelone(current, free);
}

/**
 *	@brief unset values and attributes of variables and functions
*/
void	unset(const char *str)
{
	t_envp		*shell;
	char		*var_name;

	var_name = ft_strjoin(str, "=");
	if (!var_name)
		return ;
	if (!var_name_check(var_name))
	{
		perror("unset: not a valid identifier");
		free(var_name);
		return ;
	}
	free(var_name);
	shell = get_env_struct();
	unset_env_var(str);
}

/**
 * UNSET =============================
 * 
 * [error case]	"bash: unset: `whatever': not a valid identifier"
 * 		when the variable name is not valid, but if the variable name is valid
 * 		and it doesn't exist, do nothing and print nothing
*/