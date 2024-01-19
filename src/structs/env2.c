/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:22:08 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/18 13:38:40 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief frees everything
*/
void	free_env(void)
{
	t_envp	*shell;

	shell = get_env_struct();
	if (shell->vars)
		ft_lstclear(&shell->vars, free);
	if (shell->env_array)
		free_env_array();
	if (shell->cursor)
		free (shell->cursor);
}

/**
 * @brief looks for a env variable and returns it
 * @param str the variable to find
 * @return pointer to the env variable, NULL if can't find
 * @example find_env_var("PATH");
*/
t_env_var	*get_env_var(const char *str)
{
	t_envp		*shell;
	t_env_var	*current;

	if (!str)
		return (NULL);
	shell = get_env_struct();
	current = shell->vars;
	while (current)
	{
		if (!ft_strncmp(str, current->content, ft_strlen(str)))
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * @brief looks for a env variable and returns it's value
 * @param str the variable to get the value
 * @return pointer to the variable's value, NULL if can't find it
 * @example get_env_var_value("PATH");
*/
char	*get_env_var_value(const char *str)
{
	int		i;
	char	*var;

	i = 0;
	if (!str || !get_env_var(str))
		return (NULL);
	var = get_env_var(str)->content;
	if (!var)
		return (NULL);
	var = ft_strchr(var, '=') + 1;
	if (!var[i])
		return (NULL);
	return (&var[i]);
}
