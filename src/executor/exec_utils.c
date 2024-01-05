/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:52:11 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/05 19:08:11 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* @brief Calls the builtins functions
*/
void	builtin_check(t_exec *exec, t_commands *cmd)
{
	(void)exec; //remove exec from params?
	if (ft_strncmp("echo", cmd->cmds[0], 5) == 0)
		echo(&cmd->cmds[1]);
	else if (ft_strncmp("cd", cmd->cmds[0], 3) == 0)
		cd(&cmd->cmds[1]); // Não está a funcionar corretamente porque está a ser executado dentro de um fork
	else if (ft_strncmp("pwd", cmd->cmds[0], 4) == 0)
		pwd();				// Está a executar duas vezes (probably o builtin e o exec)
	else if (ft_strncmp("export", cmd->cmds[0], 7) == 0)
		export(&cmd->cmds[1]);
	else if (ft_strncmp("unset", cmd->cmds[0], 6) == 0)
		unset(&cmd->cmds[1]);
	else if (ft_strncmp("env", cmd->cmds[0], 4) == 0)
		print_env();		// Está a executar duas vezes (probably o builtin e o exec)
	else if (ft_strncmp("exit", cmd->cmds[0], 5) == 0)
		exit(0); // Not working
	else
		return ;
	exit(0);
}
