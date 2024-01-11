/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:11:26 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/11 12:52:49 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *	@brief	Returns the amount of pipe redirections on the given string.
 *			If the prompt is not valid the returned value can be wrong!
*/
static int	get_pipe_count(char *str)
{
	int	pipe_count;
	int	i;

	pipe_count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '|' && !is_inside_quotes(str, i))
		{
			if (str[i + 1] == '|')
				i += 2;
			else
				i++;
			pipe_count++;
		}
		if (str[i])
			i++;
	}
	return (pipe_count);
}

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
				ES_ALLOC_FAIL);
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
			ES_ALLOC_FAIL);
	return (commands);
}

static int	count_commands(char **tokens, size_t pipe)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!tokens || !*tokens)
		return (0);
	while (pipe && tokens[i])
	{
		if (tokens[i][0] == RDIR_PIPE)
			pipe--;
		i++;
	}
	while (tokens[i] && tokens[i][0] != RDIR_PIPE)
	{
		if (is_redir_val(tokens[i][0]) && tokens[i][0] != RDIR_PIPE)
			i++;
		else if (!is_redir_val(tokens[i][0]))
			count++;
		i++;
	}
	return (count);
}

void	add_commands(t_commands **command_struct, char **tokens)
{
	int			i;
	int			j;
	int			pipe_count;
	t_commands	*command_node;

	i = -1;
	pipe_count = 0;
	command_node = *command_struct;
	if (!tokens || !command_struct || !*command_struct)
		return ;
	while (command_node)
	{
		command_node->cmds = malloc((count_commands(tokens, pipe_count++) + 1)
				* sizeof(char *));
		if (!command_node->cmds)
			free_and_exit(NULL, "minishell: memory alocation failed",
				ES_ALLOC_FAIL);
		j = 0;
		while (tokens[++i] && tokens[i][0] != RDIR_PIPE)
		{
			if (!is_redir_val(tokens[i][0]))
				command_node->cmds[j++] = tokens[i];
			else if (is_redir_val(tokens[i][0]))
				i++;
		}
		command_node->cmds[j] = NULL;
		command_node = command_node->next;
	}
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
