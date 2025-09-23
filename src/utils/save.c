/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:47:03 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/23 18:51:55 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_dup2(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) < 0)
			perror_exit("dup2 failed", EXIT_FAILURE);
	}
	return ;
}

void	save_pipe( int *write_in_pipe, int *read_out_pipe)
{
	int 	pipe_fds[2];

	if (pipe(pipe_fds) < 0)
		perror_exit("create_pipe failed", EXIT_FAILURE);
	*read_out_pipe = pipe_fds[0];
	*write_in_pipe = pipe_fds[1];
	return ;
}
