/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:28:17 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/13 18:49:33 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	add_cmds_loop(t_commands **cmd_nd, char **tkns, int *i, int *pp_c)
{
	int			j;

	(*cmd_nd)->cmds = malloc((count_commands(tkns, (*pp_c)++) + 1)
			* sizeof(char *));
	if (!(*cmd_nd)->cmds)
		free_and_exit(NULL, "minishell: memory alocation failed",
			ES_ALLOC_FAIL);
	j = 0;
	while (tkns[++(*i)] && tkns[*i][0] != RDIR_PIPE)
	{
		if (!is_redir_val(tkns[*i][0]))
			(*cmd_nd)->cmds[j++] = tkns[*i];
		else if (is_redir_val(tkns[*i][0]))
			(*i)++;
	}
	(*cmd_nd)->cmds[j] = NULL;
	*cmd_nd = (*cmd_nd)->next;
}

void	add_commands(t_commands **command_struct, char **tokens)
{
	int			i;
	int			pipe_count;
	t_commands	*command_node;

	i = -1;
	pipe_count = 0;
	command_node = *command_struct;
	if (!tokens || !command_struct || !*command_struct)
		return ;
	while (command_node)
		add_cmds_loop(&command_node, tokens, &i, &pipe_count);
}

void	addback_commandstruct(t_commands **lst, t_commands *new_commands)
{
	t_commands	*last;

	if (!new_commands)
		return ;
	new_commands->next = NULL;
	if (!*lst)
	{
		*lst = new_commands;
		return ;
	}
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new_commands;
	}
}

void	free_commands(t_commands **command_struct)
{
	t_commands	*tmp;
	t_commands	*node;

	if (!command_struct || !(*command_struct))
		return ;
	node = *command_struct;
	while (node)
	{
		tmp = node->next;
		node->hd_fd = to_close(node->hd_fd);
		node->read_fd = to_close(node->read_fd);
		node->write_fd = to_close(node->write_fd);
		if (node->cmds)
			free(node->cmds);
		if (node->cmd_path)
			free(node->cmd_path);
		if (node->redirects)
			free_redirections(&node->redirects);
		free(node);
		node = tmp;
	}
	get_env_struct()->commands = NULL;
	*command_struct = NULL;
}
