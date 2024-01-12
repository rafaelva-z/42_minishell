/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:52:11 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/12 20:36:03 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
*	@brief Calls the builtins functions
*/
void	builtin_exec_child(t_exec *exec, t_commands *commands)
{
	t_envp *shell;

	shell = get_env_struct();
	if (!commands || !commands->cmds || !commands->cmds[0])
		free_and_exit(exec, NULL, get_env_struct()->exit_status);
	if (ft_strncmp("echo", commands->cmds[0], 5) == 0)
		shell->exit_status = echo(&commands->cmds[1]);
	else if (ft_strncmp("pwd", commands->cmds[0], 4) == 0)
		shell->exit_status = pwd();
	else if (ft_strncmp("env", commands->cmds[0], 4) == 0)
		shell->exit_status = print_env();
	else if (ft_strncmp("cd", commands->cmds[0], 3) == 0)
		shell->exit_status = cd(&commands->cmds[1]);
	else if (ft_strncmp("export", commands->cmds[0], 7) == 0)
		shell->exit_status = export(&commands->cmds[1]);
	else if (ft_strncmp("unset", commands->cmds[0], 6) == 0)
		shell->exit_status = unset(&commands->cmds[1]);
	else if (ft_strncmp("exit", commands->cmds[0], 5) == 0)
		free_and_exit(exec, MSG_EXIT, 0);
	else
		return ;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_and_exit(exec, NULL, get_env_struct()->exit_status);
}

/**
*	@brief Calls the builtins functions
*/
int	builtin_exec_parent(t_exec *exec, t_commands *commands)
{
	t_envp *shell;

	shell = get_env_struct();
	if (commands && commands->cmds && commands->cmds[0])
	{
		if (ft_strncmp("cd", commands->cmds[0], 3) == 0)
			shell->exit_status = cd(&commands->cmds[1]);
		else if (ft_strncmp("export", commands->cmds[0], 7) == 0)
			shell->exit_status = export(&commands->cmds[1]);
		else if (ft_strncmp("unset", commands->cmds[0], 6) == 0)
			shell->exit_status = unset(&commands->cmds[1]);
		else if (ft_strncmp("exit", commands->cmds[0], 5) == 0)
			free_and_exit(exec, MSG_EXIT, 0);
		else
			return (0);
	}
	if (exec)
		free_exec(exec);
	return (1);

}

void	free_exec(t_exec *exec)
{
	if (exec->bin_dir)
		matrix_deleter(&exec->bin_dir);
	if (exec->pid)
		free (exec->pid);
	exec->fd[0] = to_close(exec->fd[0]);
	exec->fd[1] = to_close(exec->fd[1]);
	exec->remainder_fd = to_close(exec->remainder_fd);
}
