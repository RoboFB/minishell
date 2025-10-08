/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:47:33 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/06 14:58:49 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


// can be changed to run with a smaller if else block when fist setting path and then fd if path exists

void set_all_redirect(t_file *head)
{
	while (head != NULL)
	{
		if(head->type == FD_PIPE_READ || head->type == FD_HEREDOC_READ)
			set_fd(head, STDIN_FILENO);
		else if (head->type == FD_PIPE_WRITE)
			set_fd(head, STDOUT_FILENO);
		else if (head->type == PATH_STDIN_READ)
			read_file(head, STDIN_FILENO);
		else if (head->type == PATH_STDOUT_WRITE)
			write_file(head, STDOUT_FILENO);
		else if (head->type == PATH_STDOUT_WRITE_APPEND)
			write_append_file(head, STDOUT_FILENO);
		else if (head->type == PATH_STDERR_WRITE)
			write_file(head, STDERR_FILENO);
		else if (head->type == PATH_STDERR_WRITE_APPEND)
			write_append_file(head, STDERR_FILENO);
		head = head->next;
	}
	return ;
}

void	set_fd(t_file *file, int change_fd)
{
	// ft_fprintf(2, "set_fd:%d to %d  typ:%d\n", file->fd, change_fd, file->type);
	save_dup2(file->fd, change_fd);
	save_close(&file->fd);
	return ;
}

void	read_file(t_file *file, int change_fd)
{
	file->fd = open(file->path, O_RDONLY);
	if (file->fd < 0)
		perror_exit("open: input", EXIT_FAILURE);
	set_fd(file, change_fd);
	return ;
}

void	write_file(t_file *file, int change_fd)
{
	file->fd = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file->fd < 0)
		perror_exit("open: output", EXIT_FAILURE);
	set_fd(file, change_fd);
	return ;
}

void	write_append_file(t_file *file, int change_fd)
{
	file->fd = open(file->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file->fd < 0)
		perror_exit("open: append", EXIT_FAILURE);
	set_fd(file, change_fd);
	return ;
}
