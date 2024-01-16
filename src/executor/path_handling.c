/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:45:08 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/16 00:16:24 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* @brief Creates an array with the directories to the binaries. If
* PATH environment variable doesn't exists, the array is set to NULL
*/
void	bin_finder(t_exec *exec)
{
	int	i;

	if (!exec->envp->get_value("PATH"))
	{
		exec->bin_dir = NULL;
		return ;
	}
	exec->bin_dir = ft_split(exec->envp->get_value("PATH"), ':');
	if (!exec->bin_dir)
		return ;
	i = -1;
	while (exec->bin_dir[++i])
		exec->bin_dir[i] = ft_strjoin_free(exec->bin_dir[i], "/", 1);
	while (exec->bin_dir[exec->nbr_bin])
		exec->nbr_bin++;
}

int	is_path(char *str)
{
	if (!str || !*str)
		return (0);
	if ((str[0] == '.' && str[1] == '/') || str[0] == '/')
		return (1);
	return (0);
}

static int	is_path_has_acess(t_commands *cmd, t_exec *exec)
{
	if (access(cmd->cmds[0], X_OK) == 0)
	{
		cmd->cmd_path = ft_strdup(cmd->cmds[0]);
		return (1);
	}
	free_and_exit(exec, message_joiner(3, "minishell:", cmd->cmds[0],
			": Permission denied\n"), ES_K_N_AVAIL);
	return (0);
}

/*
* @brief It finds and associates the correct path to the binary of each
 corresponding command
*/
void	path_finder(t_exec *exec, t_commands *cmd, int i)
{
	int	bin_amt;

	bin_amt = 0;
	while (exec->bin_dir && exec->bin_dir[bin_amt])
		bin_amt++;
	while (exec->bin_dir && exec->bin_dir[++i])
	{
		cmd->cmd_path = ft_strjoin(exec->bin_dir[i], cmd->cmds[0]);
		if (access(cmd->cmd_path, F_OK) == 0)
			return ;
		free (cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	if (is_path(cmd->cmds[0]) && access(cmd->cmds[0], F_OK) == 0)
		if (is_path_has_acess(cmd, exec))
			return ;
	if (is_path(cmd->cmds[0]))
		free_and_exit(exec, message_joiner(3, "minishell: ",
				cmd->cmds[0], ": No such file or directory\n"), ES_CMD_N_FOUND);
	free_and_exit(exec, message_joiner(3, "minishell: ",
			cmd->cmds[0], ": command not found\n"), ES_CMD_N_FOUND);
}
