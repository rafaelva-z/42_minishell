/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:28:32 by rvaz              #+#    #+#             */
/*   Updated: 2023/12/29 19:59:02 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief sets the env variable given
 * @param name the variable to set
 * @example set_env_var("PATH", "/bin:/usr/bin");
*/
static void	set_env_var(const char *name, const char *value)
{
	t_envp		*shell;
	t_env_var	*current;
	char		*var_name;

	if (!name)
		return ;
	shell = get_env_struct();
	current = get_env_var(name);
	var_name = ft_strjoin(name, "=");
	if (!current)
		ft_lstadd_back(&shell->vars, ft_lstnew(ft_strjoin(var_name, value)));
	else
	{
		free(current->content);
		current->content = ft_strjoin(var_name, value);
	}
	free(var_name);
	//  do nothing if var and value are the same as existing one
}

/**
 *	@brief set the export attribute for variables
 *	@example export("VAR_NAME=VAR_VALUE");
*/
void	export(const char *str)
{
	char		*var_value;
	char		*var_name;
	int			i;

	i = 0;
	if (!str)
	{
		export_sort_print();
		return ;
	}
	if (!var_name_check(str))
		return ;
	while (str[i] != '=')
		i++;
	var_name = ft_substr(str, 0, i);
	var_value = ft_substr(str, i + 1, ft_strlen(str)
			- (ft_strlen(var_name) + 1));
	set_env_var(var_name, var_value);
	free(var_name);
	free(var_value);
}

/**
 * EXPORT =============================
 * 
 * 	Must begin with letter or underscore
 * 	var name can't start with a number
 * 	var name can't contain symbols or spaces
*/
