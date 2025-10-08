/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:55 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/08 11:34:00 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main way to exit the shell with exit code
void	exit_shell(t_exit_code exit_code)
{
	close_all_files(data()->tree_root);
	rl_clear_history();
	gc_clear_all();
	exit(exit_code);
}

void	perror_exit(char *msg, t_exit_code exit_code)
{
	perror(msg);
	exit_shell(exit_code);
}

void	perror_msg_exit(char *msg_start, char *msg_end, t_exit_code exit_code)
{
	ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", msg_start, strerror(errno), msg_end);
	exit_shell(exit_code);
}

void	msg_exit(char *function, char *error, t_exit_code exit_code)
{
	ft_fprintf(STDERR_FILENO, "%s: %s\n", function, error);
	exit_shell(exit_code);
}

void	msg_error(char *function, char *error)
{
	ft_fprintf(STDERR_FILENO, "%s: %s\n", function, error);
}

// set last_exit_code and return
void set_exit_code(t_exit_code exit_code)
{
	data()->last_exit_code = exit_code;
	return;
}
