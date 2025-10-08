/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:25:15 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/08 17:06:45 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// run in sub for pipes
void	exe_command_no_return(t_expression *cmd)
{
	set_all_redirect(cmd->files);
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
pid_t	exe_command_return(t_expression *cmd)
{
	pid_t	pid;
	
	if ((is_builtin(cmd)))
		run_builtin_in_main(cmd);
	else
	{
		pid = save_fork();
		if (pid > 0)
			return (pid);
		exe_command_no_return(cmd);
	}
	return (-1);
}


bool is_piped_direct(t_expression *cmd)
{
	if (cmd->parent == NULL)
		return (false);
	if (cmd->parent->type == OPERATOR_PIPE)
		return (true);
	else
		return (false);
}

// no pipe in tree above
bool is_piped_somewhere(t_expression *cmd)
{
	if (cmd->parent == NULL)
		return (false);
	while (cmd)
	{
		if (cmd->parent->type == OPERATOR_PIPE)
			return (true);
		cmd = cmd->parent;
	}
	return (false);
}

void run_builtin_in_main(t_expression *cmd)
{
	int		stdin_fd;
	int		stdout_fd;

	stdin_fd = save_dup(STDIN_FILENO);
	stdout_fd = save_dup(STDOUT_FILENO);
	set_all_redirect(cmd->files);// maby check if i leak fds here but should be fine
	run_builtin(cmd);
	save_dup2(stdin_fd, STDIN_FILENO);
	save_dup2(stdout_fd, STDOUT_FILENO);
	save_close(&stdin_fd);
	save_close(&stdout_fd);
	return ;
}

void run_comand(t_expression *cmd)
{
	char	*path_command;

	path_command = get_full_path_cmd(cmd->name, env_get_line_data("PATH"));
	if (path_command == NULL)
		msg_exit(cmd->name, "command not found", EXIT_BLT_CMD_NOT_FOUND);
	
	// if (access(path_command, X_OK) != 0) // check if executable normaly execve does this also maype for better error codes needed?
	// 	perror_msg_exit(path_command, "command not executable", EXIT_BLT_CMD_NOT_EXECUTABLE);
	execve(path_command, cmd->args, (char *const *)*env_get_ptr());
	perror_msg_exit(path_command, "execve failed", EXIT_BLT_CMD_NOT_EXECUTABLE);
}

