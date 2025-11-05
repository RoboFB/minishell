/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_syscals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:47:03 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 21:05:29 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_pipe(int *write_in_pipe, int *read_out_pipe)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		perror_exit("create_pipe failed", EXIT_GENERAL_ERROR);
	*read_out_pipe = pipe_fds[0];
	*write_in_pipe = pipe_fds[1];
	return ;
}

pid_t	save_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		signal(SIGINT, SIG_IGN);
	if (pid == -1)
		perror_exit("fork failed", EXIT_GENERAL_ERROR);
	return (pid);
}
