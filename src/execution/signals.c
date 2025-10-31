/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:29:32 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/31 17:40:25 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 Signal Name     Default Action    Comment                   POSIX

2 SIGINT     Terminate   Interrupt from keyboard, Control-C   Yes   ctrl-C
3 SIGQUIT    Dump        Quit from keyboard, Control-\        Yes   ctrl-\

ctrl-D -> EOF


*/

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 13); // Handle Ctrl+C
		rl_on_new_line();
	}
	else if (sig == SIGQUIT)
		exit_shell(data()->last_exit_code); // Handle Ctrl+\ .
}

void	signal_init(void)
{
	struct sigaction	sa;

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

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_reset(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	sig_init(void)
{
	struct sigaction	sa;

	sa.sa_handler = ctrl_c;
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
