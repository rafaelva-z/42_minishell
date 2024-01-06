/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:36:08 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/06 21:40:47 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    destroy_all(t_exec *exec, char *message, int exit_status)
{
	t_envp	*shell;
	
	if (message)
		ft_putstr_fd(message, 2);
	shell = get_env_struct();
	shell->exit_status = exit_status;
	if (exec)
		exec_destroy(exec);
	if (shell->first_cmd_struct)
		free_commands(&shell->first_cmd_struct);
	if (shell)
		destroy_env();
	exit (exit_status);
}

void	desplay_error(char *error_msg)
{
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
}