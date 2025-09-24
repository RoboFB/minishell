/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:27:14 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/24 14:36:43 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int blt_count_args(t_expression *cmd)
{
	int count;

	if (cmd->args == NULL || cmd->args[0] == NULL)
		return (0);
	count = 0;
	while (cmd->args[1 + count] != NULL)
		count++;
	return (count);
}

bool blt_has_flag(t_expression *cmd)
{

	if (blt_count_args(cmd) >= 1 && cmd->args[1][0] == '-')
		return (true);
	else
		return (false);
}