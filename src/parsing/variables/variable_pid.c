/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:58:49 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/04 18:59:14 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	receive_pid(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	data()->pid = info->si_pid;
	return ;
}

pid_t	get_pid(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &receive_pid;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR2, &sa, NULL) < 0)
		return (-1);
	kill(0, SIGUSR2);
	while (!data()->pid)
		;
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR2, &sa, NULL) < 0)
		return (-1);
	return (data()->pid);
}
