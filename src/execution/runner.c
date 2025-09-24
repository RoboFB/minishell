/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:36:02 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/23 19:01:46 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sets gc for all execution
void	run_all(t_expression *root)
{
	pid_t	pid;

	gc_mode(GC_EXECUTION);
	data()->tree_root = root;
	pid = run_tree(root);
	if (data()->last_pid != -1)
		waitpid(data()->last_pid, &data()->last_exit_code, 0);
	return ;
}

// call ones every line to run the whole tree starting from root
pid_t	run_tree(t_expression *cmd)
{
	pid_t	pid;

	pid = -1;
	if (cmd == NULL)
		return (-1);
	if (cmd->type == OPERATOR_CMD)
		pid = exe_command(cmd);
	else if (cmd->type == OPERATOR_PIPE)
		pid = exe_pipe(cmd);
	else if (cmd->type == OPERATOR_AND)
		pid = exe_and(cmd);
	else if (cmd->type == OPERATOR_OR)
		pid = exe_or(cmd);
	return (pid);
}

pid_t exe_pipe(t_expression *cmd)
{
	pid_t pid;

	save_pipe(&cmd->first->files->fd, &cmd->second->files->fd);//todo need to be created
	pid = run_tree(cmd->first);
	pid = run_tree(cmd->second);
	save_close(&cmd->first->files->fd);
	save_close(&cmd->second->files->fd);
	return (pid);
}
pid_t exe_and(t_expression *cmd)
{
	pid_t pid;
	int status;

	status = 0;
	pid = run_tree(cmd->first);
	if (pid > 0)
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data()->last_exit_code = WEXITSTATUS(status);
	if (data()->last_exit_code == 0)
		run_tree(cmd->second);
	return (pid);
}

pid_t exe_or(t_expression *cmd)
{
	pid_t pid;
	int status;

	status = 0;
	pid = run_tree(cmd->first);
	if (pid > 0)
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data()->last_exit_code = WEXITSTATUS(status);
	if (data()->last_exit_code != 0)
		run_tree(cmd->second);
	return (pid);
}
