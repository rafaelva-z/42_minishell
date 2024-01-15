/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:00:15 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/13 18:50:11 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirection	*new_redirection(int type, char *key_wrd)
{
	t_redirection	*redirect;

	redirect = malloc(sizeof(t_redirection));
	if (!redirect)
		return (NULL);
	redirect->type = type;
	redirect->key_wrd = key_wrd;
	redirect->next = NULL;
	return (redirect);
}

static void	add_redir_if(char **tokens, int *i, t_commands **command_node)
{
	t_redirection	*redirect;

	if (tokens[*i] && is_redir_val(tokens[*i][0]))
	{
		if (tokens[*i][0] == RDIR_PIPE)
		{
			*command_node = (*command_node)->next;
			(*i)++;
			return ;
		}
		redirect = new_redirection(0, NULL);
		if (!redirect)
			free_and_exit(NULL, ERR_ALLOC, ES_ALLOC_FAIL);
		if (tokens[*i][0] == RDIR_IN || tokens[*i][0] == RDIR_OUT)
			redirect->type = tokens[*i][0];
		else if (tokens[*i][0] == RDIR_APP || tokens[*i][0] == RDIR_HDOC)
			redirect->type = tokens[*i][0];
		redirect->key_wrd = tokens[++(*i)];
		addback_redirection(&(*command_node)->redirects, redirect);
	}
}

void	add_redirections(t_commands **command_struct, char **tokens)
{
	int				i;
	t_commands		*command_node;

	i = 0;
	command_node = *command_struct;
	if (!tokens || !command_struct || !*command_struct)
		return ;
	while (tokens[i] && command_node)
	{
		while (tokens[i] && !is_redir_val(tokens[i][0]))
			i++;
		add_redir_if(tokens, &i, &command_node);
	}
}

void	addback_redirection(t_redirection **lst, t_redirection *new_redir)
{
	t_redirection	*last;

	if (!new_redir)
		return ;
	new_redir->next = NULL;
	if (!*lst)
	{
		*lst = new_redir;
		return ;
	}
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

void	free_redirections(t_redirection **redirections)
{
	t_redirection	*tmp;
	t_redirection	*node;

	if (!redirections || !*redirections)
		return ;
	node = *redirections;
	while (node)
	{
		tmp = node->next;
		free(node);
		node = tmp;
	}
	*redirections = NULL;
}
