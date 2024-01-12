/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:35:44 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/12 13:08:04 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief returns a pointer to the static shell struct
*/
t_envp	*get_env_struct(void)
{
	static t_envp	shell;

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

char	**create_env_array(void)
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
		free_env_array();
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

void	free_env_array(void)
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
	shell->cursor = NULL;
	shell->env_array = NULL;
	shell->tokens = NULL;
	shell->exit_status = 0;
	shell->commands = NULL;
	shell->nbr_cmds = 0;
	shell->make_array = create_env_array;
	shell->get = get_env_var;
	shell->get_value = get_env_var_value;
	shell->set = set_env_var;
	//shell->unset = unset;
	shell->print = print_env;
	shell->print_alpha = export_sort_print;
	shell->destroy = free_env;
	if (envp && *envp)
		create_env_list(envp);
}
