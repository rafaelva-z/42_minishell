/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:45:20 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/16 23:21:32 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* @brief Initializes all variables in the executor struct
*/
static void	initializer_exec(t_exec *exec)
{
	exec->envp = get_env_struct();
	exec->bin_dir = NULL;
	exec->nbr_bin = 0;
	exec->fd[0] = -1;
	exec->fd[1] = -1;
	exec->remainder_fd = -1;
	exec->pid = malloc(sizeof(pid_t) * exec->envp->nbr_cmds);
	bin_finder(exec);
}

/**
*   @brief Rearanges the standardin/out to accomudate the proper file descriptors
*/
static void	dupper(t_commands *cmd)
{
	if (cmd->read_fd != STDIN_FILENO)
	{
		dup2(cmd->read_fd, STDIN_FILENO);
		cmd->read_fd = to_close(cmd->read_fd);
	}
	if (cmd->write_fd != STDOUT_FILENO)
	{
		dup2(cmd->write_fd, STDOUT_FILENO);
		cmd->write_fd = to_close(cmd->write_fd);
	}
}

/**
*   @brief  Deals with redirections, with file permissions 
*           and executes the command
*   @param  exec executor's struct
*   @param  cmd the command to be executed
*/
static void	executor(t_exec *exec, t_commands *cmd)
{
	if (!cmd->cmds)
		free_and_exit(exec, NULL, get_env_struct()->exit_status);
	redirect(exec, cmd);
	dupper(cmd);
	exec->remainder_fd = to_close(exec->remainder_fd);
	builtin_exec_child(exec, cmd);
	path_finder(exec, cmd, -1);
	is_directory(cmd->cmds[0], exec);
	create_env_array();
	execve(cmd->cmd_path, cmd->cmds, exec->envp->env_array);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_and_exit(exec, message_joiner(3, "minishell: ",
			cmd->cmds[0], ": command not found\n"), ES_CMD_N_FOUND);
}

/*
* @brief Waits for all children processes to finish their execution,
* recording the latest exit status
*/
static void	wait_loop(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < exec->envp->nbr_cmds)
		waitpid(exec->pid[i], &(exec->envp->exit_status), 0);
	if (WIFEXITED(exec->envp->exit_status))
		exec->envp->exit_status = WEXITSTATUS(exec->envp->exit_status);
}

/*
* @brief Manages the creation of the children processes and its
* pipes
*/
void	process_generator(void)
{
	t_exec		exec;
	t_commands	*current;
	int			i;

	if (g_signal == SIGINT)
		return ;
	initializer_exec(&exec);
	current = exec.envp->commands;
	i = -1;
	while (current)
	{
		if (current->cmds[0])
			if (exec.envp->nbr_cmds == 1 && builtin_exec_parent(&exec, current))
				return ;
		if (current->next && pipe(exec.fd) != 0)
			free_and_exit(&exec, ft_strdup("Pipe error\n"), ES_PIPE);
		fd_handler_in(&exec, current);
		exec.pid[++i] = fork();
		if (exec.pid[i] == 0)
			executor(&exec, current);
		fd_handler_out(current);
		current = current->next;
	}
	wait_loop(&exec);
	free_exec(&exec);
}
/* EXECUTOR
			[ ] verifies if files path exists
			[ ] verifies permissions
			[ ] (it does both steps 1 and 2 in the order of which they were prompted)
			[ ] check if command is a builtin
			[ ] creates path of binary
			[ ] redirections ????
			[ ] executes command (verifies if command exists)
*/
/*PROCESS GENERATOR
			Initialize the struct
			create array with binary directories
			wait for the exit status of every child process
			free all the memory and close all fds; (Maybe do it inside
				of the fd_handling function)
*/