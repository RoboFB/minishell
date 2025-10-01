/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:43:33 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/01 14:17:07 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	run_builtin(t_expression *command)
{
	if (ft_strncmp(command->name, "cd", 3) == 0)
		return (blt_cd(command));
	else if (ft_strncmp(command->name, "echo", 5) == 0)
		return (blt_echo(command));
	else if (ft_strncmp(command->name, "env", 4) == 0)
		return (blt_env(command));
	else if (ft_strncmp(command->name, "exit", 5) == 0)
		return (blt_exit(command));
	else if (ft_strncmp(command->name, "q", 2) == 0)
		return (blt_exit(command));
	else if (ft_strncmp(command->name, "export", 7) == 0)
		return (blt_export(command));
	else if (ft_strncmp(command->name, "pwd", 4) == 0)
		return (blt_pwd(command));
	else if (ft_strncmp(command->name, "unset", 6) == 0)
		return (blt_unset(command));
	return ;
}

bool	is_builtin(t_expression *command)
{
	if (ft_strncmp(command->name, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(command->name, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(command->name, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(command->name, "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(command->name, "q", 2) == 0)
		return (true);
	else if (ft_strncmp(command->name, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(command->name, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(command->name, "unset", 6) == 0)
		return (true);
	return (false);
}
