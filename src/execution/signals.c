/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:29:32 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/27 15:33:56 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include <features.h>
// # include <signal.h>

// # define _GNU_SOURCE
// # define _POSIX_C_SOURCE 200809L

# include "minishell.h"



/* 
 Signal Name     Default Action    Comment                   POSIX

2 SIGINT     Terminate   Interrupt from keyboard, Control-C   Yes   ctrl-C
3 SIGQUIT    Dump        Quit from keyboard, Control-\        Yes   ctrl-\

ctrl-D -> EOF


*/

void handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 13); // Handle Ctrl+C
		rl_on_new_line();
	}
	else if (sig == SIGQUIT)
		exit_shell(data()->last_exit_code); // Handle Ctrl+\ .
}

void signal_init(void)
{
	struct sigaction sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);

	// sa_quit.sa_handler = sigquit_handler;
	// sigemptyset(&sa_quit.sa_mask);
	// sa_quit.sa_flags = 0;
	// sigaction(SIGQUIT, &sa_quit, NULL);

	return ;
}

void sig_reset(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void sig_init(void)
{
	// struct sigaction sa;
	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
