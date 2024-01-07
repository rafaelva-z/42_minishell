/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:45:20 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/07 19:05:03 by rvaz             ###   ########.fr       */
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
*	@brief Rearanges the standardin/out to accomudate the proper file descriptors
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
*	@brief	Deals with redirections, with file permissions 
*			and executes the command
*	@param	exec executor's struct
*	@param	cmd the command to be executed
*/
static void	executor(t_exec *exec, t_commands *cmd)
{
	if (!cmd->cmds)						//	this has to be here in case theres no command (ex: << EOF)
		destroy_all(exec, NULL, get_env_struct()->exit_status);
	redirect(exec, cmd);
	dupper(cmd);
	exec->remainder_fd = to_close(exec->remainder_fd);
	builtin_check(exec, cmd);
	path_finder(exec, cmd);
	create_env_array();
	execve(cmd->cmd_path, cmd->cmds, exec->envp->env_array);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	destroy_all(exec, ft_strdup("command could not execute\n"), CMD_N_FOUND);
}

/*
* @brief Managed all open file descriptors at the begging of the execution
*/
static void	fd_handler_in(t_exec *exec, t_commands *cmd)
{
	if (exec->remainder_fd > 0)
		cmd->read_fd = exec->remainder_fd;
	else
		cmd->read_fd = STDIN_FILENO;
	if (exec->fd[1] > 0)
		cmd->write_fd = exec->fd[1];
	else
		cmd->write_fd = STDOUT_FILENO;
}

/*
* @brief Managed all open file descriptors at the end of the execution
*/
static void	fd_handler_out(t_exec *exec)
{
	exec->remainder_fd = to_close(exec->remainder_fd);
	exec->remainder_fd = exec->fd[0];
	exec->fd[1] = to_close(exec->fd[1]);
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

	if (g_signal == 2)
		return ;
	initializer_exec(&exec);
	current = exec.envp->first_cmd_struct;
	i = -1;
	while (current)
	{
		if (exec.envp->nbr_cmds == 1 && builtin_check(&exec, current))
			return ;
		if (current->next && pipe(exec.fd) != 0)
			destroy_all(&exec, ft_strdup("Pipe error\n"), ES_PIPE);
		fd_handler_in(&exec, current);
		exec.pid[++i] = fork();
		if (exec.pid[i] == 0)
			executor(&exec, current);
		fd_handler_out(&exec);
		current = current->next;
	}
	wait_loop(&exec);
	exec_destroy(&exec);
}
/* EXECUTOR
			[ ]	verifies if files path exists
			[ ]	verifies permissions
			[ ]	(it does both steps 1 and 2 in the order of which they were prompted)
			[ ]	check if command is a builtin
			[ ]	creates path of binary
			[ ]	redirections ????
			[ ]	executes command (verifies if command exists)
*/

/*PROCESS GENERATOR
			Initialize the struct
			create array with binary directories
			wait for the exit status of every child process
			free all the memory and close all fds; (Maybe do it inside
				of the fd_handling function)
*/