/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:04 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/02 15:46:51 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void blt_exit(t_expression *cmd)
{
	int exit_code;

	exit_code = data()->last_exit_code;
	ft_fprintf(2, "exit\n");
	if (blt_has_flag(cmd))
	{
		msg_error("exit", "no options allowed");
		switch_exit(cmd, EXIT_SYNTAX_ERROR);
		return ;
	}
	else if (blt_count_args(cmd) >= 2)
	{
		msg_error("exit", "too many arguments");
		switch_exit(cmd, EXIT_SYNTAX_ERROR);
		return ;
	}
	if (blt_count_args(cmd) == 1)
	{
		if (blt_one_arg(cmd->args[1], INT_MIN, INT_MAX, &exit_code) == -1)
		{
			msg_error("exit", "numeric argument required");
			switch_exit(cmd, EXIT_GENERAL_ERROR);
			return ;
		}
		exit_code = exit_code % 256;
	}
	exit_shell(exit_code);
}

