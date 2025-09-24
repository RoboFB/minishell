/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:25:15 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/23 19:00:58 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// at the end to execute a command based on t_command struct

// start of one command execution
pid_t	exe_command(t_expression *cmd)
{
	char	*path_command;
	pid_t	pid;
	
	pid = fork();
	if (pid > 0)
	{
		data()->last_pid = pid;
		return (pid);
	}
	else if (pid == -1)
		return (soft_perror(NULL, -1));

	set_all_redirect(cmd->files);

	try_builtin(cmd);
	path_command = get_full_path_cmd(cmd->name, env_get_line_data("PATH"));
	if (path_command == NULL)
		msg_exit(cmd->name, "command not found", EXIT_FAILURE);
	
		// debug
	printf("full path: %s\n", path_command);
	for (int i = 0; cmd->args[i] != NULL; i++)
		printf("args: %s\n", cmd->args[i]);
	
	if (execve(path_command, cmd->args, (char *const *)*env_get_ptr()) < 0)
		perror_msg_exit(path_command, "execve failed", EXIT_FAILURE);
	return (-1);
}
