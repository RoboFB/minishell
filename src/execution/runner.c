/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:36:02 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/02 16:36:06 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sets gc for all execution
void	run_all(void)
{
	pid_t	pid;

	gc_mode(GC_EXECUTION);
	pid = run_tree(data()->tree_root);
	// wait_and_set_exit_code(pid);
	return ;
}

// call ones every line to run the whole tree starting from root
pid_t	run_tree(t_expression *cmd)
{
	pid_t	pid;

	pid = -1;
	if (cmd == NULL)
		return (-1);
	else if (cmd->type == OPERATOR_CMD)
		pid = exe_command(cmd);
	else if (cmd->type == OPERATOR_PIPE)
		pid = exe_pipe(cmd);
	else if (cmd->type == OPERATOR_AND)
		pid = exe_and(cmd);
	else if (cmd->type == OPERATOR_OR)
		pid = exe_or(cmd);
	wait_and_set_exit_code(pid);
	return (pid);
}

pid_t exe_pipe(t_expression *cmd)
{
	pid_t pid;

	file_add_front(&cmd->first->files);
	cmd->first->files->type = FD_PIPE_WRITE;
	file_add_front(&cmd->second->files);
	cmd->second->files->type = FD_PIPE_READ;
	save_pipe(&cmd->first->files->fd, &cmd->second->files->fd);
	pid = run_tree(cmd->first);
	pid = run_tree(cmd->second);
	save_close(&cmd->first->files->fd);
	save_close(&cmd->second->files->fd);
	return (pid);
}
pid_t exe_and(t_expression *cmd)
{
	pid_t pid;

	pid = run_tree(cmd->first);
	wait_and_set_exit_code(pid);
	if (data()->last_exit_code == 0)
		run_tree(cmd->second);
	return (pid);
}

pid_t exe_or(t_expression *cmd)
{
	pid_t pid;

	pid = run_tree(cmd->first);
	wait_and_set_exit_code(pid);
	if (data()->last_exit_code != 0)
		pid = run_tree(cmd->second);
	return (pid);
}

void wait_and_set_exit_code(pid_t pid)
{
	int status;

	status = 0;
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data()->last_exit_code = WEXITSTATUS(status);
	}
}

// TODO: add inherittaino of files from parent to child: in file to first   out file to all childs
