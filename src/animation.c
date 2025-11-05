/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:45:46 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/05 15:21:10 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	animation(void)
{
	const char	*frames[20] = {
		STYLE BG_CUSTOM "196" AND BOLD START " minishel🚂" END, 
		STYLE BG_CUSTOM "197" AND BOLD START " minishe🚂 " END, 
		STYLE BG_CUSTOM "198" AND BOLD START " minish🚂l " END, 
		STYLE BG_CUSTOM "199" AND BOLD START " minis🚂ll " END, 
		STYLE BG_CUSTOM "200" AND BOLD START " mini🚂ell " END, 
		STYLE BG_CUSTOM "201" AND BOLD START " min🚂hell " END, 
		STYLE BG_CUSTOM "207" AND BOLD START " mi🚂shell " END, 
		STYLE BG_CUSTOM "213" AND BOLD START " m🚂ishell " END, 
		STYLE BG_CUSTOM "219" AND BOLD START " 🚂nishell " END, 
		STYLE BG_CUSTOM "225" AND BOLD START "🚂inishell " END,
		STYLE BG_CUSTOM "231" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "230" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "229" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "228" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "227" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "226" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "220" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "214" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "208" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "202" AND BOLD START " minishell " END
	};
	const t_expression sleep = {OPERATOR_CMD, NULL, NULL, NULL, "/bin/sleep", (char *[]){"/bin/sleep", ".09", NULL}, 0, NULL, (t_tokens){NULL, NULL, 0}};
	static int	t;
	int			pid;

	while (1)
	{
		if (t >= 20)
		{
			t = 0;
			// exit_shell(0);
		}
		// usleep(50000);
		pid = run_cmd_switch((t_expression *)&sleep);
		waitpid(pid, NULL, 0);
		// wait_and_set_exit_code(pid);
		if (data()->last_exit_code)
			ft_printf("\033[s\r" STYLE BG_RED START " %3d " END "%s %% \033[u", data()->last_exit_code, frames[t]);
		else
			ft_printf("\033[s\r" STYLE BOLD AND BG_GREEN START "  🗸  " END "%s %% \033[u", frames[t]);
		t++;
	}
}

// void	animation_triggers(int sig)
// {
// 	if (sig == SIGUSR2)
// 		exit_shell(0);
// }

// void	animation_signal(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = animation_triggers;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sigaction(SIGUSR2, &sa, NULL);
// }

void	animation_init(void)
{
	if (isatty(STDIN_FILENO))
	{
		data()->animation = fork();
		// ft_printf("_num2:_%d\n", data()->animation);
		if (data()->animation)
			return;
		// animation_signal();
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
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

		kill(data()->animation, SIGKILL);
		waitpid(data()->animation, NULL, 0);
	}
}
