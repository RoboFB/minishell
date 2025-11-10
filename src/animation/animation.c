/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:45:46 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/07 15:34:27 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	animation_print(int t, bool *emote)
{
	if (data()->last_exit_code && !*emote && t < 20)
	{
		ft_printf("\033[s\r" STYLE BG_RED START " %s " END
			"%s %% \033[u", frame_emote(t), animation_switch(t));
		if (t == 19)
			*emote = true;
	}
	else if (data()->last_exit_code)
	{
		ft_printf("\033[s\r" STYLE BG_RED START " %3d " END
			"%s %% \033[u", data()->last_exit_code, animation_switch(t));
	}
	else
		ft_printf("\033[s\r" STYLE BOLD AND BG_GREEN START
			"  🗸  " END "%s %% \033[u", animation_switch(t));
}

void	animation(void)
{
	static int	t;
	bool		emote;

	emote = false;
	busy_wait(3000000, 3);
	while (1)
	{
		if (t >= 20)
			t = 0;
		animation_print(t, &emote);
		busy_wait(30000000, 3);
		t++;
	}
}

void	animation_end(int sig)
{
	(void)sig;
	exit_shell(0);
}

void	animation_init(void)
{
	struct sigaction	sa;

	if (isatty(STDIN_FILENO) && data()->animation_enabled)
	{
		data()->animation = fork();
		if (data()->animation)
			return ;
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
	if (isatty(STDIN_FILENO) && data()->animation_enabled)
	{
		kill(data()->animation, SIGUSR2);
		waitpid(data()->animation, NULL, 0);
		data()->animation_variant++;
		if (data()->animation_variant > 7)
			data()->animation_variant = 0;
	}
}
