/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:09 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/25 17:15:56 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	blt_unset(t_expression *cmd)
{
	int	idx;

	// Handel - as error
	if (blt_has_flag(cmd))
	{
		msg_exit("unset", "no options allowed", EXIT_FAILURE);
	}
	idx = 0;
	while (cmd->args && cmd->args[idx])
	{
		if (ft_strchr(cmd->args[idx], '=') == NULL)
			env_remove_line(cmd->args[idx]);
	}
	switch_exit(cmd, EXIT_SUCCESS);
}
