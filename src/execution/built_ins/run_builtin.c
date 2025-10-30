/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:43:33 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/30 16:40:38 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*h_get_builtin(t_expression *command)
{
	if (command->name == NULL)
		return (&blt_noname);
	else if (ft_strncmp(command->name, "cd", 3) == 0)
		return (&blt_cd);
	else if (ft_strncmp(command->name, "echo", 5) == 0)
		return (&blt_echo);
	else if (ft_strncmp(command->name, "env", 4) == 0)
		return (&blt_env);
	else if (ft_strncmp(command->name, "exit", 5) == 0)
		return (&blt_exit);
	else if (ft_strncmp(command->name, "q", 2) == 0)
		return (&blt_exit);
	else if (ft_strncmp(command->name, "export", 7) == 0)
		return (&blt_export);
	else if (ft_strncmp(command->name, "pwd", 4) == 0)
		return (&blt_pwd);
	else if (ft_strncmp(command->name, "unset", 6) == 0)
		return (&blt_unset);
	else
		return (NULL);
}

void	run_builtin(t_expression *command)
{
	void	(*function_pointer)(t_expression *);

	function_pointer = h_get_builtin(command);
	if (function_pointer != NULL)
		function_pointer(command);
	return ;
}

bool	is_builtin(t_expression *command)
{
	return (h_get_builtin(command) != NULL);
}
