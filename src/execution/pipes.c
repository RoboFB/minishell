/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:25:15 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/31 17:54:07 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_piped_direct(t_expression *cmd)
{
	if (cmd->parent == NULL)
		return (false);
	if (cmd->parent->type == OPERATOR_PIPE)
		return (true);
	else
		return (false);
}

// no pipe in tree above
bool	is_piped_somewhere(t_expression *cmd)
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
