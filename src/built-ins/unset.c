/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:28:39 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/17 18:48:11 by fda-estr         ###   ########.fr       */
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
	t_env_var	*next;

	shell = get_env_struct();
	next = shell->vars->next;
	if (!name || !shell->vars)
		return ;
	current = shell->get(name);
	if (!current)
		return ;
	if (current->previous)
		current->previous->next = current->next;
	if (current->next)
		current->next->previous = current->previous;
	if (next && !current->previous)
		shell->vars = next;
	else if (!next && !current->previous)
		shell->vars = NULL;
	ft_lstdelone(current, free);
}

/**
 *	@brief unset values and attributes of variables and functions
*/
int	unset(char **cmds)
{
	char	*var_name;
	int		i;

	i = 0;
	while (cmds[i])
	{
		var_name = ft_strjoin(cmds[i], "=");
		if (!var_name)
			free_and_exit(NULL, ERR_ALLOC, ES_ALLOC_FAIL, 0);
		if (!var_name_check(var_name))
		{
			free(var_name);
			i++;
			continue ;
		}
		free(var_name);
		unset_env_var(cmds[i++]);
	}
	return (0);
}

/**
 * UNSET =============================
 * 
 * [error case]	"bash: unset: `whatever': not a valid identifier"
 * 		when the variable name is not valid, but if the variable name is valid
 * 		and it doesn't exist, do nothing and print nothing
*/