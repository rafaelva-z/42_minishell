/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handeling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:45:08 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/04 18:49:42 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* ATENTION! Still to do the error handeling */

/*
* @brief Creates an array with the directories to the binaries. If
* PATH environment variable doesn't exists, the array is set to NULL
*/
void	bin_finder(t_exec *exec)
{
	int	i;

	exec->bin_dir = ft_split(exec->envp->get_value("PATH"), ':');
	if (!exec->bin_dir)
		return ;
	i = -1;
	while (exec->bin_dir[++i])
		exec->bin_dir[i] = ft_strjoin_free(exec->bin_dir[i], "/", 1);
	while (exec->bin_dir[exec->nbr_bin])
		exec->nbr_bin++;
}

/*
* @brief It finds and associates the correct path to the binary of each
 corresponding command
*/
void	path_finder(t_exec *exec, t_commands *cmd)
{
	int	i;
	int bin_amt;

	i = -1;
	bin_amt = 0;
	while (exec->bin_dir[bin_amt])
		bin_amt++;
	while (exec->bin_dir[++i])
	{
		cmd->cmd_path = ft_strjoin(exec->bin_dir[i], cmd->cmds[0]);
		if (access(cmd->cmd_path, F_OK) == 0 || i == bin_amt - 1)
			break ;
		free (cmd->cmd_path);
	}
	if (access(cmd->cmd_path, F_OK) == 0)
		return ;
	if (access(cmd->cmds[0], F_OK) == 0)
	{
		if (access(cmd->cmds[0], X_OK) == 0)
		{
			cmd->cmd_path = ft_strdup(cmd->cmds[0]);
			return ;
		}
	}
	// you have to make it so that it executes a file in the current directory. ex: ./minishell
		ft_printf("Error3\n") ;			// Error handeling
}

// /*
// * @brief takes the environment array and atributes to each command the
// * correct path to it's binary
// */
// void	command_path(t_data *data, t_exec *exec)
// {
// 	t_commands *current;

// 	current = data->first_cmd;
// 	bin_finder(exec);
// 	while (current)
// 	{
// 		if (!exec->bin_dir)
// 		{
// 			current->cmd_path = ft_strdup(current->cmds[0]);
// 			continue ;
// 		}
// 		path_finder(exec, current);
// 	}

// }

