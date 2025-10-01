/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:25:15 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/01 14:36:27 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// at the end to execute a command based on t_command struct

// start of one command execution  -1 no pid set becous not forked
pid_t	exe_command(t_expression *cmd)
{
	pid_t	pid;
	
	gc_mode(GC_EXECUTION);
	// debung_print_tree(21, cmd, 0);
	if ((is_builtin(cmd) && is_single_command(cmd)))
	{
		run_builtin_in_main(cmd);
		return (-1);
	}
	pid = save_fork();
	if (pid > 0)
		return (pid);
	set_all_redirect(cmd->files);
	close_all_files(data()->tree_root);
	run_builtin(cmd);
	run_comand(cmd);
	return (-1);
}

bool is_single_command(t_expression *cmd)
{
	if (cmd->parent == NULL)
		return (true);
	if (cmd->parent->type == OPERATOR_PIPE)
		return (false);
	else
		return (true);
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

	// debug printing
	// ft_debugf(20,"execve: path: %s", path_command);
	// for (int i = 0; cmd->args[i] != NULL; i++)
		// ft_debugf(20, "args: %s\n", cmd->args[i]);
		
	// if (access(path_command, X_OK) != 0) // check if executable normaly execve does this also maype for better error codes needed?
	// 	perror_msg_exit(path_command, "command not executable", EXIT_BLT_CMD_NOT_EXECUTABLE);
	execve(path_command, cmd->args, (char *const *)*env_get_ptr());
	perror_msg_exit(path_command, "execve failed", EXIT_BLT_CMD_NOT_EXECUTABLE);
}

