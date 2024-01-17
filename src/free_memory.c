/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:55:19 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/17 20:26:13 by fda-estr         ###   ########.fr       */
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

static char	close_std(void)
{
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
}

void	free_and_exit(t_exec *exec, char *mssg, int exit_status, int std)
{
	t_envp	*shell;

	if (std)
		close_std();
	if (mssg)
	{
		ft_putstr_fd(mssg, 2);
		free (mssg);
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
