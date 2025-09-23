/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:55 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/23 15:57:55 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prints errno
void	perror_exit(char *msg, int exit_code)
{
	perror(msg);
	gc_clear_all();
	exit(exit_code);
}

// prints errno
void	perror_msg_exit(char *msg_start, char *msg_end, int exit_code)
{
	ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", strerror(errno), msg_start, msg_end);
	gc_clear_all();
	exit(exit_code);
}

// prints custom message  function: message\n
void	msg_exit(char *function, char *error, int exit_code)
{
	ft_fprintf(STDERR_FILENO, "%s: %s\n", function, error);
	gc_clear_all();
	exit(exit_code);
}




int	soft_perror(char *msg, int exit_code)
{
	perror(msg);
	// gc_clear_all();
	data()->last_exit_code = exit_code;
	return (exit_code);
}

int	soft_msg(char *function, char *error, int exit_code)
{
	ft_fprintf(STDERR_FILENO, "%s: %s\n", function, error);
	// gc_clear_all();
	data()->last_exit_code = exit_code;
	return (exit_code);
}
