/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:59:29 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/18 16:14:19 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief	Allocates the prompt cursor to param "char **cursor".
 * 			the cursor will be the username + the constant CURSOR
 * 			or just the constant CURSOR if there is no USER variable
*/
void	get_prompt_cursor(void)
{
	t_envp	*shell;

	shell = get_env_struct();
	if (shell->cursor)
		free(shell->cursor);
	if (get_env_var("USER"))
	{
		shell->cursor = get_env_var("USER")->content + 5;
		shell->cursor = ft_strjoin(shell->cursor, CURSOR);
		shell->cursor = ft_strjoin_free("\e[92m", shell->cursor, 2);
		shell->cursor = ft_strjoin_free("\e[1m", shell->cursor, 2);
	}
}
