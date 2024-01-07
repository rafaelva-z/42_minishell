/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handeling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:45:08 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/07 20:33:36 by fda-estr         ###   ########.fr       */
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
		// printf("aqui\n");
		exec->bin_dir = NULL;
		return ;
	}
	// printf("nao era suporto vir parar aqui\n");
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
	if (access(cmd->cmds[0], F_OK) == 0)
	{
		if (access(cmd->cmds[0], X_OK) == 0)
		{
			cmd->cmd_path = ft_strdup(cmd->cmds[0]);
			return ;
		}
		destroy_all(exec, message_joiner(3 ,"minishell: ", cmd->cmds[0],
					": Permission denied\n"), K_N_AVAIL);
	}
	destroy_all(exec, message_joiner(2 , cmd->cmds[0], ": command not found\n")
			, CMD_N_FOUND);
}

/*		*/