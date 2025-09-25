/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:55 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/25 17:10:03 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main way to exit the shell with exit code
void	exit_shell(int exit_code)
{
	gc_clear_all();
	exit(exit_code);
}


// prints errno
void	perror_exit(char *msg, int exit_code)
{
	perror(msg);
	exit_shell(exit_code);
}

// prints errno
void	perror_msg_exit(char *msg_start, char *msg_end, int exit_code)
{
	ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", msg_start, strerror(errno), msg_end);
	exit_shell(exit_code);
}

// prints custom message  function: message\n
void	msg_exit(char *function, char *error, int exit_code)
{
	ft_fprintf(STDERR_FILENO, "%s: %s\n", function, error);
	exit_shell(exit_code);
}

void	msg_error(char *function, char *error)
{
	ft_fprintf(STDERR_FILENO, "%s: %s\n", function, error);
}

// (exit_shell) or (set last_exit_code and return)
void switch_exit(t_expression *cmd, int exit_code)
{
	if (!is_single_command(cmd))
		exit_shell(exit_code);
	data()->last_exit_code = exit_code;
	return;
}
