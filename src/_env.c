/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:35:44 by rvaz              #+#    #+#             */
/*   Updated: 2023/09/28 14:36:40 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief returns a pointer to the static shell struct
*/
t_envp	*get_env_struct(void)
{
	static t_envp shell;

	return (&shell);
}

/**
 * @brief creates a linked list with all existing env variables and stores it
 * 		  on the static shell struct
*/
void	create_env_list(char **envp)
{
	t_envp	*shell;
	int		i;

	shell = get_env_struct();
	i = 0;
	if (!envp)
		return ;
	shell->vars = ft_lstnew(strdup(envp[i]));
	while (envp[++i])
		ft_lstadd_back(&shell->vars, ft_lstnew(strdup(envp[i])));
}

char	**create_env_array()
{
	t_envp		*shell;
	t_env_var	*tmp;
	int			env_len;
	int			i;

	shell = get_env_struct();
	if (!shell->vars)
		return (NULL);
	tmp = shell->vars;
	i = 0;
	env_len = ft_lstsize(shell->vars);
	if (shell->env_array)
		destroy_env_array();
	shell->env_array = malloc((env_len + 1) * sizeof(char *));
	if (!shell->env_array)
		exit(0);
	while (tmp)
	{
		shell->env_array[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	shell->env_array[i] = NULL;
	return (shell->env_array);
}

void	destroy_env_array()
{
	t_envp	*shell;
	int		i;

	shell = get_env_struct();
	i = 0;
	if (!shell->env_array)
		return ;
	while (shell->env_array[i])
		free(shell->env_array[i++]);
	free(shell->env_array);
}

/**
 * @brief initializes the env struct (to be run at the begining of
 * 		  the program)
*/
void	init_env(char **envp)
{
	t_envp		*shell;

	shell = get_env_struct();
	shell->env_array = NULL;
	shell->make_array = create_env_array;
	shell->get = get_env_var;
	shell->get_value = get_env_var_value;
	shell->set = export;
	shell->unset = unset;
	shell->print = print_env;
	shell->print_alpha = export_sort_print;
	shell->destroy = destroy_env;

	create_env_list(envp);
}

/**
 * @brief frees everything
*/
void	destroy_env()
{
	t_envp	*shell;

	shell = get_env_struct();
	if (shell->vars)
		ft_lstclear(&shell->vars, free);
	if (shell->env_array)
		destroy_env_array();
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
	char		*var_name;

	if (!str)
		return (NULL);
	shell = get_env_struct();
	current = shell->vars;
	var_name = ft_strjoin(str, "=");
	if (!var_name)
		return (NULL);
	while (current)
	{
		if (!ft_strncmp(var_name, current->content, ft_strlen(var_name)))
		{
			free(var_name);
			return (current);
		}
		current = current->next;
	}
	free(var_name);
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
