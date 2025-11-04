/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:55 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 15:57:19 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prints msg to stderr and returns
void	msg_error(char *function, char *error)
{
	ft_fprintf(STDERR_FILENO, "%s: %s\n", function, error);
	return ;
}

// set last_exit_code and returns
void	set_exit_code(t_exit_code exit_code)
{
	data()->last_exit_code = exit_code;
	return ;
}
