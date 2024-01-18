/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:28:32 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/18 14:14:47 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * EXPORT =============================
 * 
 * 	var names	must begin with letter or underscore
 * 				can't start with a number
 * 				can't contain symbols or spaces
*/

/**
 * @brief sets the env variable given
 * @param name the variable to set
 * @example set_env_var("PATH", "/bin:/usr/bin");
*/
void	set_env_var(const char *name, const char *value)
{
	t_env_var	*current;
	char		*var_name;

	if (!name)
		return ;
	current = get_env_var(name);
	if (value)
		var_name = ft_strjoin(name, "=");
	else
		var_name = ft_strdup(name);
	if (!current)
		ft_lstadd_back(&get_env_struct()->vars,
			ft_lstnew(ft_strjoin_free(var_name, value, 1)));
	else
	{
		free(current->content);
		current->content = ft_strjoin_free(var_name, value, 1);
	}
}

/**
 * @brief helper function to export function
*/
static void	export_set_env_var(char *cmds, int j)
{
	char	*var_value;
	char	*var_name;

	var_value = NULL;
	var_name = ft_substr(cmds, 0, j);
	if (cmds[j] == '\0')
		set_env_var(var_name, NULL);
	else
	{
		var_value = ft_substr(cmds, j + 1, ft_strlen(&(cmds[j + 1])));
		set_env_var(var_name, var_value);
	}
	free(var_name);
	if (var_value)
		free(var_value);
}

/**
 *	@brief set the export attribute for variables
*/
int	export(char **cmds)
{
	int		i;
	int		j;
	int		exit_status;

	i = -1;
	exit_status = 0;
	if (!cmds || !cmds[0])
		return (export_sort_print());
	while (cmds[++i])
	{
		j = 0;
		if (!var_name_check(cmds[i]))
		{
			exit_status = display_error(ERR_EXPORT_BAD_NAME, 1);
			continue ;
		}
		while (cmds[i][j] && cmds[i][j] != '=')
			j++;
		export_set_env_var(cmds[i], j);
	}
	return (exit_status);
}
