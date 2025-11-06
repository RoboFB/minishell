/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:36:02 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/06 15:22:21 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// call ones every line to run the whole tree starting from root
pid_t	run_tree(t_expression *cmd)
{
	pid_t	pid;

	pid = -1;
	if (cmd == NULL)
		return (-1);
	gc_mode(GC_TEMPORARY);
	inherit_files(cmd);
	if (cmd->type == OPERATOR_CMD)
		pid = run_cmd_switch(cmd);
	else if (cmd->type == OPERATOR_PIPE)
		pid = run_pipe(cmd);
	else if (cmd->type == OPERATOR_AND || cmd->type == OPERATOR_OR)
		pid = run_and_or(cmd);
	close_all_files(cmd);
	wait_and_set_exit_code(pid);
	return (pid);
}

pid_t	run_pipe(t_expression *cmd)
{
	pid_t	pid_1;
	pid_t	pid_2;

	pipe_add_front(cmd);
	pid_1 = save_fork();
	if (pid_1 == 0)
	{
		pid_1 = run_tree(cmd->first);
		msg_exit("Programming error", "pipes 1", EXIT_GENERAL_ERROR);
	}
	save_close(&cmd->first->files->fd);
	if (is_piped_direct(cmd))
	{
		pid_2 = run_tree(cmd->second);
		msg_exit("Programming error", "pipes 2", EXIT_GENERAL_ERROR);
	}
	pid_2 = save_fork();
	if (pid_2 == 0)
	{
		pid_2 = run_tree(cmd->second);
		msg_exit("Programming error", "pipes 3", EXIT_GENERAL_ERROR);
	}
	save_close(&cmd->second->files->fd);
	wait_and_set_exit_code(pid_1);
	return (pid_2);
}

pid_t	run_and_or(t_expression *cmd)
{
	(void)run_tree(cmd->first);
	if ((data()->last_exit_code == 0 && cmd->type == OPERATOR_AND)
		|| (data()->last_exit_code != 0 && cmd->type == OPERATOR_OR))
	{
		(void)run_tree(cmd->second);
	}
	if (is_piped_direct(cmd))
	{
		exit_shell(data()->last_exit_code);
	}
	return (-1);
}

void	wait_and_set_exit_code(pid_t pid)
{
	int	status;

	status = 0;
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			data()->last_exit_code = WTERMSIG(status) + EXIT_SIGNAL_BASE;
		else if (WIFEXITED(status))
			data()->last_exit_code = WEXITSTATUS(status);
		sig_init();
	}
}
