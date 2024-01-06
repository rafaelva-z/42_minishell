/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:36:08 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/06 20:11:47 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    destroy_all(t_exec *exec)
{
	t_envp	*shell;
	int		exit_status;
	
	shell = get_env_struct();
	exit_status = shell->exit_status;
	if (exec)
		exec_destroy(exec);
	if (shell->first_cmd_struct)
		free_commands(&shell->first_cmd_struct);
	if (shell)
		destroy_env();
	exit (exit_status);
}
