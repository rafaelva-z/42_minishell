/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:46:05 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/18 17:37:44 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_bltn(t_exec *exec, char **cmds, short print_exit)
{
	char	exit_status;

	exit_status = 0;
	if (print_exit)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!cmds || !cmds[0])
		return (free_and_exit(exec, NULL, 0, 0));
	if (!cmds[0][0] || !contains_only_nbr(cmds[0]))
		return (free_and_exit(exec, ft_strdup(ERR_EXIT_NUM_ARG), 2, 0));
	if (count_cmds(cmds) > 1)
		return (free_and_exit(exec, ft_strdup(ERR_EXIT_TOO_MANY_ARG), 1, 0));
	exit_status = ft_atoi(cmds[0]);
	free_and_exit(exec, NULL, exit_status, 0);
}
