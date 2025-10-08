/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:09 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/08 11:28:47 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	blt_unset(t_expression *cmd)
{
	int	idx;

	if (blt_has_flag(cmd))
	{
		msg_error("unset", "no options allowed");
		set_exit_code(EXIT_SYNTAX_ERROR);
		return ;
	}
	idx = 1;
	while (cmd->args && cmd->args[idx])
	{
		if (ft_strchr(cmd->args[idx], '=') == NULL)
			env_remove_line(cmd->args[idx]);
		idx++;
	}
	set_exit_code(EXIT_OK);
	return ;
}
