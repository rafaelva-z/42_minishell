/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:01:04 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/12 21:06:51 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	prompt_processing(char **prompt)
{
	if (quote_check(*prompt))
	{
		free(*prompt);
		get_env_struct()->exit_status = ES_OP_N_PERM;
		return (display_error(ERR_QUOTES, -1));
	}
	prompt_cleaner(prompt);
	if (redirection_check(*prompt))
	{
		free(*prompt);
		get_env_struct()->exit_status = ES_OP_N_PERM;
		return (display_error(ERR_RDIR, -2));
	}
	add_spaces_redirections(prompt);
	return (0);
}
