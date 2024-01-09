/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:56:23 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/09 20:58:14 by rvaz             ###   ########.fr       */
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
static void	sighandler_main(int signal) // MAIN
{
	if (signal == SIGINT)
	{
		g_signal = 0;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

static void	sighandler_child_heredoc(int signal) // CHILD
{
	(void)signal;
	//write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
	g_signal = SIGINT;
}

static void	sighandler_loop(int signal) // inside LOOP 
{
	(void)signal;
	g_signal = SIGINT;
	//write(1, "\n", 1);
	return ;
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
		sig_int.sa_handler = sighandler_main;
		g_signal = 0;
	}
	else if (process == HNDLR_CHILD_HD)
		sig_int.sa_handler = sighandler_child_heredoc;
	else if (process == HNDLR_LOOP)
		sig_int.sa_handler = sighandler_loop;
	else if (process == 4)
		sig_int.sa_handler = SIG_IGN;
	sig_quit.sa_handler = SIG_IGN;
	sig_int.sa_flags = 0;
	sig_quit.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
