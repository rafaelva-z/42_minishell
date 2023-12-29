/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 03:02:07 by rvaz              #+#    #+#             */
/*   Updated: 2023/12/28 19:26:56 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_inside_quotes(char *str, int index)
{
	char	c;

	c = 0;
	if (!str || index < 0 || index > (int)ft_strlen(str))
		return (0);
	while (*str && index--)
	{
		if (!c)
		{
			if (*str == SQUOTE || *str == DQUOTE)
				c = *str;
		}
		else if (c == *str)
			c = 0;
		str++;
	}
	if (c == *str)
		c = 0;
	return ((c == SQUOTE) + ((c == DQUOTE) * 2));
}



/**
 *	@brief	checks on the given string what is the next character type ignoring
 *			spaces.
 *	@return	0 if the next character is alphanumeric or a symbol, a positive number if the next
 *			character is a redirection, -1 if the next character is a NULL character
*/
static int	check_after_redir(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (is_redir(*str))
		return (what_redir(str));
	else if (*str == '\0')
		return (-1);
	return (0);
}

/**
 *	@brief	check for synthax errors about redirections
*/
int	redirection_check(char *prompt)
{
	int	redir_type;
	int	after_redir_type;
	int	i;

	i = 0;
	if (prompt[i] == '|')
	{
		perror("-minishell: syntax error near unexpected token 'insert token?'"); // this couple lines could be in a error handler func;
		return (2);
	}
	while (prompt[i])
	{
		while (prompt[i] && !is_redir(prompt[i]))
			i++;
		if (is_redir(prompt[i]) && !is_inside_quotes(prompt, i))
		{
			redir_type = what_redir(&prompt[i]);
			if (redir_type == RDIR_DPIPE) // double pipe
			{
				perror("-minishell: Double pipe"); // this couple lines could be in a error handler func;
				return (2);
			}
			else if (redir_type == RDIR_APP || redir_type == RDIR_HDOC || redir_type == RDIR_DPIPE)
				i += 2;
			else if (redir_type == RDIR_IN || redir_type == RDIR_OUT || redir_type == RDIR_PIPE)
				i++;
			after_redir_type = check_after_redir(&prompt[i]); // need to do this func
			if (after_redir_type > 0 && after_redir_type != RDIR_PIPE && after_redir_type != RDIR_DPIPE) // found a non pipe redirect
			{
				if (redir_type == RDIR_PIPE)
					continue ;
				else
				{
					perror("-minishell: syntax error near unexpected token 'insert token?'"); // this couple lines could be in a error handler func;
					return (2);
				}
			}
			else if (after_redir_type == -1 || after_redir_type == RDIR_PIPE || after_redir_type == RDIR_DPIPE) // found a '\0' || found a pipe redirect
			{
				perror("-minishell: syntax error near unexpected token 'insert token?'"); // this couple lines could be in a error handler func;
				return (2);
			}
		}
		i++;
	}
	return (0);
}

/**
 *	@brief	Returns the amount of pipe redirections on the given string.
 *			If the prompt is not valid the returned value can be wrong!
*/
// int	pipe_count(char *str) // MUST NOT COUNT PIPES INSIDE QUOTES OR DQUOTES "|"
// {
// 	int	pipe_count;

// 	pipe_count = 0;
// 	while (str)
// 	{
// 		if (*str == RDIR_PIPE && /*is not between quotes*/)
// 		{
// 			if (str[1] == RDIR_PIPE)
// 				str += 2;
// 			else
// 				str++;
// 			pipe_count++;
// 		}
// 		str++;
// 	}
// 	return (pipe_count);
// }

// t_redirectlst	redir_getredir_struct(char *prompt, t_commandstruct **command_struct)
// {
// 	t_redirectlst	redir_list;
// 	t_commandstruct	*command_struct_node;

// 	while (*prompt && *prompt != '|')
// 	{
// 		while (*prompt && !is_redir(*prompt))
// 			prompt++;
// 		if (is_redir(*prompt) && /* is not between quotes */)
// 		{
// 			if (*prompt == prompt[1])
// 			{
// 				if (*prompt == '>')
// 					addback_redirlist(command_struct_node->redir_list, RDIR_APP);
// 				if (*prompt == '<')
// 					addback_redirlist(command_struct_node->redir_list, RDIR_HDOC);
// 			}
// 			else
// 			{
// 				if (*prompt == '>')
// 					addback_redirlist(command_struct_node->redir_list, RDIR_OUT);
// 				else if (*prompt == '<')
// 					addback_redirlist(command_struct_node->redir_list, RDIR_IN);
// 				else if (*prompt == '|')
// 				{
// 					addback_commandstruct(command_struct, command_struct_node);
// 					redir_getredir_struct(++prompt, command_struct);
// 					break ;
// 				}
// 			}
// 			while (!ft_isalnum(prompt))
// 				prompt++;
// 			last_redirlist()->str = malloc(wordlen(prompt));
// 			ft_strncpy(prompt, last_redirlist()->str, new_strlen(prompt)); //this strlen should copy a string that may be inside 
// 		}
// 	}
// 	return (redir_list);
// }

// /**
//  *	@brief	creates a t_command_struct linked list with a node for each pipe on
//  *			the give prompt. For each node, create a linked list with the
//  * 			redirect information (file name and type).
//  * 
// **/
// t_command_struct	get_command_struct(char *prompt) // DONE I GUESS
// {
// 	t_commandstruct **command_struct
// 	int	pipe_count;

// 	if (!hasredir(prompt))
// 		return (NULL);
// 	if (redir_check_token_error(prompt))
// 		return (NULL);
// 	pipe_count = get_pipe_amount(prompt); // make this function
// 	command_struct = crate_command_linkedlist(command_struct, pipe_count); // make this function to allocat the full commands linked list
// 	if (!command_struct);
// 	{
// 		perror("MEMORY ERROR");
// 		exit(-10000);
// 	}
// 	return (redir_getredir_linkedlists(prompt, command_struct, pipecount)); 
// }
