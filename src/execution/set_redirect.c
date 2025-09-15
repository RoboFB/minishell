/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:47:33 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/12 21:16:49 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"




void run_command(t_command *cmd)
{
	if(cmd->child_type == CHILD_PIPE)
		child_pipe(cmd);
	// else if (cmd->child_type == CHILD_AND)
		// child_and(cmd);
	// else if (cmd->child_type == CHILD_OR)
		// child_or(cmd);
	
	else if (cmd->child_type == REDIRECTION_INPUT)
		redirect_input(cmd);
	else if (cmd->child_type == REDIRECTION_OUTPUT)
		redirect_output(cmd);
	else if (cmd->child_type == REDIRECTION_ERROR)
		redirect_error(cmd);
	else if (cmd->child_type == REDIRECTION_APPEND)
		redirect_append(cmd);
	else if (cmd->child_type == REDIRECTION_HERE_DOC)
		redirect_here_doc(cmd);
	
	return ;
}


void	child_pipe(t_command *command)
{
	(void)command;

	int		pipe_fds[2];

	save_pipe(pipe_fds);
	fork();

	return ;
}


void	redirect_input(t_command *command)
{
	int		file_fd;

	file_fd = open(command->file, O_RDONLY);
	if (file_fd < 0)
		perror_exit("open: input", EXIT_FAILURE);

	save_dup2(file_fd, STDIN_FILENO);
	save_close(file_fd);
	return ;
}


void	redirect_output(t_command *command)
{
	int		file_fd;

	file_fd = open(command->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd < 0)
		perror_exit("open: output", EXIT_FAILURE);

	save_dup2(file_fd, STDOUT_FILENO);
	save_close(file_fd);
	return ;
}

void	redirect_error(t_command *command)
{
	int		file_fd;

	file_fd = open(command->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd < 0)
		perror_exit("open: error", EXIT_FAILURE);

	save_dup2(file_fd, STDERR_FILENO);
	save_close(file_fd);
	return ;
}

void	redirect_append(t_command *command)
{
	int		file_fd;

	file_fd = open(command->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd < 0)
		perror_exit("open: append", EXIT_FAILURE);

	save_dup2(file_fd, STDOUT_FILENO);
	save_close(file_fd);
	return ;
}

void	redirect_here_doc(t_command *command)
{
	int		file_fd;

	file_fd = open(command->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd < 0)
		perror_exit("open: append", EXIT_FAILURE);

	save_dup2(file_fd, STDOUT_FILENO);
	save_close(file_fd);
	return ;
}