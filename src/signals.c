/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:56:23 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/07 19:58:16 by rvaz             ###   ########.fr       */
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
static void	sighandler(int signal)
{
	//	wait pid for pipe
	if (signal == SIGINT)
	{
		g_signal = 2;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

/**
 * @brief defines signal behaviour
*/
void	set_signals(void)
{
	struct sigaction	sig_c;
	struct sigaction	sig_d;
	sigset_t			block_mask;

	(void)block_mask;  //may not be needed
	sigemptyset(&sig_c.sa_mask);
	sigemptyset(&sig_d.sa_mask);
	sig_c.sa_handler = sighandler;
	sig_d.sa_handler = SIG_IGN;
	sig_c.sa_flags = 0;
	sig_d.sa_flags = 0;
	sigaction(SIGINT, &sig_c, NULL);
	sigaction(SIGQUIT, &sig_d, NULL);
}
