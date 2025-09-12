/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:25:15 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/12 19:09:12 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/* void	exe_command(t_command *cmd)
{
	char	*path_command;

	path_command = get_path_command(cmd->command, get_environment_line_ptr("PATH"));// error handling
	if (path_command == NULL)
	{
		ft_putstr_fd(cmd->command, STDERR_FILENO);
		error_exit_msg(": command not found");
	}
	if (execve(path_command, cmd->args, (char *const *)*env_get_ptr()) < 0) // todo
	{
		free(path_command);
		free_split(command_with_args);
		error_exit_errno("execve failed");
	}
	return ;
} */