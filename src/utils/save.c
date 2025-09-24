/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:47:03 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/24 17:53:11 by rgohrig          ###   ########.fr       */
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

void	save_pipe(int *write_in_pipe, int *read_out_pipe)
{
	int 	pipe_fds[2];

	if (pipe(pipe_fds) < 0)
		perror_exit("create_pipe failed", EXIT_FAILURE);
	*read_out_pipe = pipe_fds[0];
	*write_in_pipe = pipe_fds[1];
	return ;
}


// mallocates buffer if buf is NULL internally without gc
char *save_getcwd(char *buf, size_t size)
{
	char *path;

	path = getcwd(buf, size);
	if (path == NULL)
		perror_exit("getcwd failed", EXIT_FAILURE);
	return (path);
}

void save_chdir(const char *new_dir)
{
	if (chdir(new_dir) < 0)
		perror_exit("chdir failed", EXIT_FAILURE);
	return ;
}