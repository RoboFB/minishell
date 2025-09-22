/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:55 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/19 19:04:32 by rgohrig          ###   ########.fr       */
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

// prints custom message  function: message\n
void	msg_exit(char *function, char *error, int exit_code)
{
	ft_fprintf(STDERR_FILENO, "%s: %s\n", function, error);
	gc_clear_all();
	exit(exit_code);
}
