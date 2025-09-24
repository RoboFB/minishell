/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:04 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/24 18:02:45 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void blt_exit(t_expression *cmd)
{
	int exit_code;

	exit_code = data()->last_exit_code;
	if (blt_has_flag(cmd))
		msg_exit("exit", "no options allowed", EXIT_FAILURE);
	else if (blt_count_args(cmd) >= 2)
		msg_exit("exit", "too many arguments", EXIT_FAILURE);
	if (blt_count_args(cmd) == 1)
	{
		if (blt_one_arg(cmd->args[1], INT_MIN, INT_MAX, &exit_code) == -1)
			msg_exit("exit", "numeric argument required", EXIT_FAILURE);
		exit_code = exit_code % 256;
	}
	exit(exit_code);
}

