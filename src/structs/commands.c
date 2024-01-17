/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:11:26 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/17 20:15:36 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief	Hepler function of create_command_linkedlist
*/
static void	initialize_command_struct(t_commands *node)
{
	node->cmds = NULL;
	node->cmd_path = NULL;
	node->redirects = NULL;
	node->hd_fd = -1;
	node->read_fd = -1;
	node->write_fd = -1;
	node->next = NULL;
}

/**
 * @brief	Hepler function of get_command_linkedlst
*/
static t_commands	*create_command_linkedlist(int node_amount)
{
	t_commands	*commands_2;
	t_commands	*node;
	t_envp		*shell;

	shell = get_env_struct();
	commands_2 = NULL;
	while (node_amount)
	{
		node = malloc(sizeof(t_commands));
		if (!node)
			free_and_exit(NULL, "minishell: memory alocation failed",
				ES_ALLOC_FAIL, 0);
		if (shell->commands == NULL)
			shell->commands = node;
		initialize_command_struct(node);
		if (!commands_2)
			commands_2 = node;
		else
			addback_commandstruct(&commands_2, node);
		node_amount--;
	}
	return (commands_2);
}

/**
 *	@brief	creates a t_commands linked list with a node for each pipe on
 *			the give prompt. For each node, create a linked list with the
 * 			redirect information (file name and type).
 * 
**/
t_commands	*get_command_linkedlst(char *prompt)
{
	t_commands	*commands;
	t_envp		*shell;

	shell = get_env_struct();
	if (!prompt)
		return (NULL);
	shell->nbr_cmds = get_pipe_count(prompt) + 1;
	commands = create_command_linkedlist(shell->nbr_cmds);
	if (!commands)
		free_and_exit(NULL, "minishell: memory alocation failed",
			ES_ALLOC_FAIL, 0);
	return (commands);
}
