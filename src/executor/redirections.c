/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:44:42 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/07 18:21:50 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	ATENTION: if theres no input on the fist command, it should read from
				the standard input*/

/*
* @brief Verifies the acess and opens the redirection of the infiles (<)
*/
void	redir_in(t_exec *exec, t_commands *cmd, t_redirection *redir)
{
	(void) exec;		//it should be passed as an argument, so the memory can be freed in case of process termination
	if (access(redir->key_wrd, F_OK) == -1)
		ft_printf("Error4\n");		//	Error handling
	if (access(redir->key_wrd, R_OK) == -1)
		ft_printf("Error5\n");		//	Error handling
	if (cmd->read_fd > 2)
		cmd->read_fd = to_close(cmd->hd_fd);
	cmd->read_fd = open(redir->key_wrd, O_RDONLY);
}

/*
* @brief Verifies the acess and opens the redirection of the out files (>)
*/
void	redir_out_trunc(t_exec *exec, t_commands *cmd, t_redirection *redir)
{
	(void)exec;		//it should be passed as an argument, so the memory can be freed in case of process termination
	if (access(redir->key_wrd, F_OK) == -1)
	{
		if (cmd->write_fd > 2)
			cmd->write_fd = to_close(cmd->write_fd);
		cmd->write_fd = open(redir->key_wrd, O_WRONLY | O_CREAT , S_IRUSR | S_IWUSR);
		return ;
	}
	if (access(redir->key_wrd, W_OK) == -1)
		ft_printf("Error6\n");		//	Error handling
	if (cmd->write_fd > 2)
		cmd->write_fd = to_close(cmd->write_fd);
	cmd->write_fd = open(redir->key_wrd, O_RDONLY, O_TRUNC);
}

/*
* @brief Verifies the acess and opens the redirection of the append files (>>)
*/
void	redir_out_append(t_exec *exec, t_commands *cmd, t_redirection *redir)
{
	(void)exec;		//it should be passed as an argument, so the memory can be freed in case of process termination
	if (access(redir->key_wrd, F_OK) == -1)
	{
		if (cmd->write_fd > 2)
			cmd->write_fd = to_close(cmd->write_fd);
		cmd->write_fd = open(redir->key_wrd, O_WRONLY | O_CREAT , S_IRUSR | S_IWUSR | O_APPEND);
		return ;
	}
	if (access(redir->key_wrd, W_OK) == -1)
		ft_printf("Error7\n");		//	Error handling
	if (cmd->write_fd > 2)
		cmd->write_fd = to_close(cmd->write_fd);
	cmd->write_fd = open(redir->key_wrd, O_RDONLY, O_APPEND);
}

/*
* @brief Verifies the acess and opens the redirection files in the order that
* it was prompted
*/
void	redirect(t_exec *exec, t_commands *cmd)
{
	t_redirection	*current;

	current = cmd->redirects;
	while (current)
	{
		if (current->type == RDIR_IN)
			redir_in(exec, cmd, current);
		else if (current->type == RDIR_HDOC && !current->next)
			cmd->read_fd = cmd->hd_fd;
		else if (current->type == RDIR_OUT)
			redir_out_trunc(exec, cmd, current);
		else if (current->type == RDIR_APP)
			redir_out_append(exec, cmd, current);
		current = current->next;
	}
}