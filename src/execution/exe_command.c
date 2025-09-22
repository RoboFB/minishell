/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:25:15 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/19 19:04:37 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// at the end to execute a command based on t_command struct

void	exe_command(t_command *cmd)
{
	char	*path_command;

	try_builtin(cmd);
	path_command = get_full_path_cmd(cmd->name, env_get_line_data("PATH"));
	if (path_command == NULL)
		msg_exit(cmd->name, "command not found", EXIT_FAILURE);
	if (execve(path_command, cmd->args, (char *const *)*env_get_ptr()) < 0)
		msg_exit("execve", "failed", EXIT_FAILURE);
	return ;
}
