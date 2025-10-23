/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:04 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/23 13:20:40 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void blt_exit(t_expression *cmd)
{
	int exit_code;


	// ft_fprintf(2, "exit\n");
	if (blt_has_flag(cmd) && !ft_isdigit(cmd->args[1][1]))
	{
		msg_error("exit", "no options allowed");
		exit_code = EXIT_SYNTAX_ERROR;
	}
	else if (blt_count_args(cmd) == 0)
	{
		exit_code = data()->last_exit_code;
	}
	else if (h_is_num(cmd->args[1]))
	{
		if (blt_count_args(cmd) >= 2)
		{
			msg_error("exit", "too many arguments");
			set_exit_code(EXIT_GENERAL_ERROR);
			return ;
		}
		exit_code = ft_atoi(cmd->args[1]) % 256;
	}
	else
	{
		msg_error("exit", "numeric argument required");
		exit_code = EXIT_SYNTAX_ERROR;
	}


	exit_shell(exit_code);
}






bool	h_is_num(const char *num_ptr)
{
	size_t			len;

	if (num_ptr == NULL || *num_ptr == '\0')
		return (false);
	len = 0;
	if (num_ptr[len] == '-' || num_ptr[len] == '+')
		len++;
	while (num_ptr[len])
	{
		if (!ft_isdigit(num_ptr[len]))
			break;
		len++;
	}
	return (len == ft_strlen(num_ptr));
}
