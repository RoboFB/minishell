/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:09 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/19 19:03:41 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	blt_unset(t_command *cmd)
{
	int	idx;

	// Handel - as error
	if (cmd->args && cmd->args[0] && cmd->args[1] && cmd->args[1][0] == '-')
	{
		msg_exit("unset", "no options allowed", EXIT_FAILURE);
	}
	idx = 0;
	while (cmd->args && cmd->args[idx])
	{
		if (ft_strchr(cmd->args[idx], '=') == NULL)
			env_remove_line(cmd->args[idx]);
	}
	gc_clear_all();
	exit(EXIT_SUCCESS);
}
