/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:47:03 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/12 21:15:14 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_close(int fd)
{
	if (close(fd) < 0)
		perror_exit("close failed", EXIT_FAILURE);
	return ;
}

void	save_dup2(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) < 0)
			perror_exit("dup2 failed", EXIT_FAILURE);
	}
	return ;
}

void	save_pipe(int *one_pipe)
{
	if (pipe(one_pipe) < 0)
		perror_exit("create_pipe failed", EXIT_FAILURE);
	return ;
}


/* // 
void	close_one_pip(int *pipe)
{
	if (close(pipe[0]) < 0
		|| close(pipe[1]) < 0)
		error_exit_errno("close pipe fds failed");
	return ;
}
 */