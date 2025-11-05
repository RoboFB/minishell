/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:29:32 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/05 15:22:32 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 Signal Name     Default Action    Comment                   POSIX

2 SIGINT     Terminate   Interrupt from keyboard, Control-C   Yes   ctrl-C
3 SIGQUIT    Dump        Quit from keyboard, Control-\        Yes   ctrl-\

ctrl-D -> EOF
*/

void	ctrl_c(int sig)
{
	(void)sig;
	animation_kill();
	ft_printf("\033[s\r" " %3d  minishell  %% \033[u\n", data()->last_exit_code );

	// ft_printf("%s\n", "\r\033[5C" " minishell " " % ");
	rl_replace_line("", 0);
	rl_on_new_line();
	set_exit_code(sig + EXIT_SIGNAL_BASE);
	rl_redisplay();
	animation_init();
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
	// kill(data()->animation, SIGUSR2);
}
