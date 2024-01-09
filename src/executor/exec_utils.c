/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:52:11 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/09 14:46:59 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_exec_child(t_exec *exec, t_commands *commands)
{
	if (!commands || !commands->cmds || !commands->cmds[0])
		destroy_all(exec, NULL, get_env_struct()->exit_status);
	if (ft_strncmp("echo", commands->cmds[0], 5) == 0)
		echo(&commands->cmds[1]);
	else if (ft_strncmp("pwd", commands->cmds[0], 4) == 0)
		pwd();				// Está a executar duas vezes (probably o builtin e o exec)
	else if (ft_strncmp("env", commands->cmds[0], 4) == 0)
		print_env();		// Está a executar duas vezes (probably o builtin e o exec)
	else
		return ;
	destroy_all(exec, NULL, get_env_struct()->exit_status);
}

/*
* @brief Calls the builtins functions
*/
int	builtin_exec_parent(t_exec *exec, t_commands *commands)
{
	if (commands && commands->cmds && commands->cmds[0])
	{
		if (ft_strncmp("cd", commands->cmds[0], 3) == 0)
			cd(&commands->cmds[1]); // Não está a funcionar corretamente porque está a ser executado dentro de um fork
		else if (ft_strncmp("export", commands->cmds[0], 7) == 0)
			export(&commands->cmds[1]);
		else if (ft_strncmp("unset", commands->cmds[0], 6) == 0)
			unset(&commands->cmds[1]);
		else if (ft_strncmp("exit", commands->cmds[0], 5) == 0)
			exit_shell(exec);
		else
			return (0);
	}
	if (exec)
		exec_destroy(exec);
	return (1);

}

void	exec_destroy(t_exec *exec)
{
	if (exec->bin_dir)
		matrix_deleter(exec->bin_dir);
	if (exec->pid)
		free (exec->pid);
	exec->fd[0] = to_close(exec->fd[0]);
	exec->fd[1] = to_close(exec->fd[1]);
	exec->remainder_fd = to_close(exec->remainder_fd);
}
