/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:25:15 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 16:32:26 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_builtin_in_main(t_expression *cmd)
{
	int	stdin_fd;
	int	stdout_fd;

	stdin_fd = save_dup(STDIN_FILENO);
	stdout_fd = save_dup(STDOUT_FILENO);
	if (set_all_redirect(cmd->files) == 0)
	{
		run_builtin(cmd);
	}
	save_dup2(stdin_fd, STDIN_FILENO);
	save_dup2(stdout_fd, STDOUT_FILENO);
	save_close(&stdin_fd);
	save_close(&stdout_fd);
	return ;
}

static void	run_comand(t_expression *cmd)
{
	char	*path_command;

	path_command = get_cmd_path(cmd->name, env_get_line_data("PATH"));
	if (path_command == NULL)
		msg_exit(cmd->name, "command not found", EXIT_BLT_CMD_NOT_FOUND);
	if (access(path_command, X_OK) != 0)
		perror_msg_exit(path_command, "", EXIT_BLT_CMD_NOT_FOUND);
	execve(path_command, cmd->args, (char *const *)*env_get_ptr());
	perror_msg_exit(path_command, "execve failed", EXIT_BLT_CMD_NOT_EXECUTABLE);
}

// run in sub for pipes
static void	run_cmd_no_return(t_expression *cmd)
{
	sig_reset();
	if (set_all_redirect(cmd->files) != 0)
		exit_shell(data()->last_exit_code);
	close_all_files(data()->tree_root);
	if (is_builtin(cmd))
	{
		run_builtin(cmd);
		exit_shell(data()->last_exit_code);
	}
	else
		run_comand(cmd);
}

// run in main single command no pipe
static pid_t	run_cmd_return(t_expression *cmd)
{
	pid_t	pid;

	if ((is_builtin(cmd)))
		run_builtin_in_main(cmd);
	else
	{
		pid = save_fork();
		if (pid > 0)
			return (pid);
		run_cmd_no_return(cmd);
	}
	return (-1);
}

pid_t	run_cmd_switch(t_expression *cmd)
{
	resolve(cmd);
	if (is_piped_direct(cmd))
	{
		run_cmd_no_return(cmd);
		return ((pid_t)(-1));
	}
	else
		return (run_cmd_return(cmd));
}
