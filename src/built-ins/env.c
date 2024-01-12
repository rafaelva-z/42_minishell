/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:08:37 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/12 16:03:25 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *	@brief print enviroment variables
*/
int	print_env(void)
{
	t_envp		*shell;
	t_env_var	*current;

	shell = get_env_struct();
	current = shell->vars;
	if (current)
		ft_lstiter(current, var_printcontent);
	return (0);
}
