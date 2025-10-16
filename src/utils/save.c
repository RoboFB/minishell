/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:47:03 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/10 15:51:20 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_dup2(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) == -1)
			perror_exit("dup2 failed", EXIT_GENERAL_ERROR);
	}
	return ;
}

int	save_dup(int copy_fd)
{
	int new_fd;
	new_fd = dup(copy_fd);
	if (new_fd == -1)
		perror_exit("dup failed", EXIT_GENERAL_ERROR);
	return (new_fd);
}


void	save_pipe(int *write_in_pipe, int *read_out_pipe)
{
	int 	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		perror_exit("create_pipe failed", EXIT_GENERAL_ERROR);
	*read_out_pipe = pipe_fds[0];
	*write_in_pipe = pipe_fds[1];
	return ;
}


// mallocates buffer if buf is NULL internally needs null check (no gc)
char *save_getcwd(char *buf, size_t size)
{
	char *path;

	path = getcwd(buf, size);
	if (path == NULL)
		perror_exit("getcwd failed", EXIT_GENERAL_ERROR); // maby not exit here if i dont have permission
	return (path);
}

void save_chdir(const char *new_dir)
{
	if (chdir(new_dir) == -1)
		perror_exit("chdir failed", EXIT_GENERAL_ERROR);
	return ;
}

pid_t save_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror_exit("fork failed", EXIT_GENERAL_ERROR);
	return (pid);
}
