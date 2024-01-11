/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:56:23 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/11 12:54:29 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/types.h>
#include <signal.h>

/**
 * 	Work in progress
 * 	CTRL + C = SIGINT
 * 	CTRL + \ = SIGQUIT
 * 	CTRL + D = EOF
**/
static void	sighandler_main(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 0;
		get_env_struct()->exit_status = ES_SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

static void	sighandler_child_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		rl_clear_signals();
		close(STDIN_FILENO);
	}
}

static void	sighandler_loop(int signal)
{
	if (signal == SIGINT)
		g_signal = SIGINT;
}

/**
 * @brief defines signal behaviour
*/
void	set_signals(int process)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;
	sigset_t			block_mask;

	(void)block_mask;  //may not be needed
	sigemptyset(&sig_int.sa_mask);
	sigemptyset(&sig_quit.sa_mask);
	if (process == HNDLR_MAIN)
	{
		g_signal = 0;
		sig_int.sa_handler = sighandler_main;
	}
	else if (process == HNDLR_CHILD_HD)
		sig_int.sa_handler = sighandler_child_heredoc;
	else if (process == HNDLR_LOOP)
		sig_int.sa_handler = sighandler_loop;
	sig_quit.sa_handler = SIG_IGN;
	sig_int.sa_flags = 0;
	sig_quit.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
