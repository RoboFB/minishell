/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:55 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/31 17:47:06 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg_error(char *function, char *error)
{
	ft_fprintf(STDERR_FILENO, "%s: %s\n", function, error);
}

// set last_exit_code and return
void	set_exit_code(t_exit_code exit_code)
{
	data()->last_exit_code = exit_code;
	return ;
}
