/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:45:46 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/05 21:46:19 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	animation(void)
{
	static int	t;
	bool		emote;
	
	emote = false;
	while (1)
	{
		if (t >= 20)
			t = 0;
		if (data()->last_exit_code && !emote && t < 20)
		{
			ft_printf("\033[s\r" STYLE BG_RED START " %s " END "%s %% \033[u", frame_emote(t), frame_fish(0));
			if (t == 19)
				emote = true;
		}
		else if (data()->last_exit_code)
		{
			ft_printf("\033[s\r" STYLE BG_RED START " %3d " END "%s %% \033[u", data()->last_exit_code, frame_fish(t));
		}
		else
			ft_printf("\033[s\r" STYLE BOLD AND BG_GREEN START "  🗸  " END "%s %% \033[u", frame_fish(t));
		busy_wait(30000000, 3);
		t++;
	}
}

void	busy_wait(int iterations, int divider)
{
	int			counter;
	unsigned	work;

	counter = 0;
	work = 50;
	if (divider == 0)
		divider = 3;
	while (counter < iterations)
	{
		work *= work;
		work /= divider;
		counter++;
	}
	return ;
}

void	animation_end(int sig)
{
	(void)sig;
	exit_shell(0);
}

void	animation_init(void)
{
	struct sigaction	sa;
	
	if (isatty(STDIN_FILENO))
	{
		data()->animation = fork();
		// ft_printf("_num2:_%d\n", data()->animation);
		if (data()->animation)
			return;
		// animation_signal();
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		sa.sa_handler = animation_end;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGUSR2, &sa, NULL);
		animation();
		
	}
}

void	animation_kill(void)
{
	if (isatty(STDIN_FILENO))
	{
		// if (data()->last_exit_code)
		// 	ft_printf("\033[s\r" STYLE START " %3d " END " minishell  %% \033[u", data()->last_exit_code);
		// else
		// 	ft_printf("\033[s\r" STYLE START "  🗸  " END " minishell  %% \033[u");

		kill(data()->animation, SIGUSR2);
		waitpid(data()->animation, NULL, 0);
	}
}
