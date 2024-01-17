/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:55:19 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/17 23:31:44 by rvaz             ###   ########.fr       */
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

static void	close_std(void)
{
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
}

void	free_and_exit(t_exec *exec, char *msg, int exit_status, int std)
{
	t_envp	*shell;

	if (std)
		close_std();
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		free (msg);
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
