/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:28:29 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/07 17:06:58 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *	@brief exit the minishell
 *	-1 -128 kernel stopped the program 
 *	0 sucessful
 *	1-127 error
*/
void	exit_shell(t_exec *exec)
{
	t_envp	*shell;

	shell = get_env_struct();
	destroy_all(exec, ft_strdup("exit\n"), shell->exit_status);
}
