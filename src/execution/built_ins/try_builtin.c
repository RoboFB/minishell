/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:43:33 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/19 19:03:53 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	try_builtin(t_command *command)
{
	if (ft_strncmp(command->name, "cd", 3) == 0)
		blt_cd(command);
	else if (ft_strncmp(command->name, "echo", 5) == 0)
		blt_echo(command);
	else if (ft_strncmp(command->name, "env", 4) == 0)
		blt_env(command);
	else if (ft_strncmp(command->name, "exit", 5) == 0)
		blt_exit(command);
	else if (ft_strncmp(command->name, "export", 7) == 0)
		blt_export(command);
	else if (ft_strncmp(command->name, "pwd", 4) == 0)
		blt_pwd(command);
	else if (ft_strncmp(command->name, "unset", 6) == 0)
		blt_unset(command);
	else
		return ;
	msg_exit(command->name, "builtin error", EXIT_FAILURE);
}
