/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:28:32 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/13 13:33:52 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	var_name = ft_strjoin(name, "=");
	if (!current)
		ft_lstadd_back(&get_env_struct()->vars,
			ft_lstnew(ft_strjoin(var_name, value)));
	else
	{
		free(current->content);
		current->content = ft_strjoin(var_name, value);
	}
	free(var_name);
}

/**
 *	@brief set the export attribute for variables
 *	@example export("VAR_NAME=VAR_VALUE");
*/
int	export(char **cmds)
{
	char	*var_value;
	char	*var_name;
	int		i;
	int		j;

	i = -1;
	if (!cmds[0])
		return (export_sort_print());
	while (cmds[++i])
	{
		j = 0;
		if (!var_name_check(cmds[i]))
			return (display_error("minishell: export: invalid option\n", 1));
		while (cmds[i][j] != '=')
			j++;
		var_name = ft_substr(cmds[i], 0, j);
		var_value = ft_substr(cmds[i], j + 1, ft_strlen(&(cmds[i][j + 1])));
		set_env_var(var_name, var_value);
		free(var_name);
		free(var_value);
	}
	return (0);
}

/**
 * EXPORT =============================
 * 
 * 	Must begin with letter or underscore
 * 	var name can't start with a number
 * 	var name can't contain symbols or spaces
*/
