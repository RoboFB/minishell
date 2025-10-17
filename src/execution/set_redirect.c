/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:47:33 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/17 12:07:00 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


// can be changed to run with a smaller if else block when fist setting path and then fd if path exists

// R: -1 = Error prints message allready and set error code
int set_all_redirect(t_file *head)
{
	int	return_val;

	return_val = 0;
	while (head != NULL)
	{
		if(head->type == FD_PIPE_READ || head->type == FD_HEREDOC_READ)
			set_fd(head, STDIN_FILENO);
		else if (head->type == FD_PIPE_WRITE)
			set_fd(head, STDOUT_FILENO);
		else if (head->type == PATH_STDIN_READ)
			return_val = read_file(head, STDIN_FILENO);
		else if (head->type == PATH_STDOUT_WRITE)
			return_val = write_file(head, STDOUT_FILENO);
		else if (head->type == PATH_STDOUT_WRITE_APPEND)
			return_val = write_append_file(head, STDOUT_FILENO);
		else if (head->type == PATH_STDERR_WRITE)
			return_val = write_file(head, STDERR_FILENO);
		else if (head->type == PATH_STDERR_WRITE_APPEND)
			return_val = write_append_file(head, STDERR_FILENO);
		if (return_val != 0)
			break;
		head = head->next;
	}
	return (return_val);
}

int	set_fd(t_file *file, int change_fd)
{
	save_dup2(file->fd, change_fd);
	save_close(&file->fd);
	return (0);
}

int	read_file(t_file *file, int change_fd)
{
	if (file->path == NULL)
	{
		msg_error("in", "ambiguous redirect");
		set_exit_code(EXIT_GENERAL_ERROR);
		return (-1);
	}
	file->fd = open(file->path, O_RDONLY);
	if (file->fd  == -1)
	{
		perror(file->path);
		return (-1);
	}
	set_fd(file, change_fd);
	return (0);
}

int	write_file(t_file *file, int change_fd)
{
	if (file->path == NULL)
	{
		msg_error("out", "ambiguous redirect");
		set_exit_code(EXIT_GENERAL_ERROR);
		return (-1);
	}
	file->fd = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file->fd == -1)
	{
		perror(file->path);
		return (-1);
	}
	set_fd(file, change_fd);
	return (0);
}

int	write_append_file(t_file *file, int change_fd)
{
	if (file->path == NULL)
	{
		msg_error("append", "ambiguous redirect");
		set_exit_code(EXIT_GENERAL_ERROR);
		return (-1);
	}
	file->fd = open(file->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file->fd  == -1)
	{
		perror(file->path);
		return (-1);
	}
	set_fd(file, change_fd);
	return (0);
}
