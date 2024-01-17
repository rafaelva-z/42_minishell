/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:55:19 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/17 18:37:01 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_matrix_and_commands(void)
{
	t_envp	*shell;

	shell = get_env_struct();
	if (shell->tokens)
		matrix_deleter(&shell->tokens);
	if (shell->commands)
		free_commands(&shell->commands);
}

void	free_and_exit(t_exec *exec, char *message, int exit_status, int std)
{
	t_envp	*shell;

	if (std)
	{
		close (STDIN_FILENO);
		close (STDOUT_FILENO);
	}
	if (message)
	{
		ft_putstr_fd(message, 2);
		free (message);
	}
	shell = get_env_struct();
	shell->exit_status = exit_status;
	if (exec)
		free_exec(exec);
	if (shell->tokens)
	{
		matrix_deleter(&shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->commands)
		free_commands(&shell->commands);
	if (shell)
		free_env();
	exit (exit_status);
}
