/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_noname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:27:01 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/20 15:28:43 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	blt_noname(t_expression *command)
{
	if (command->name == NULL)
		set_exit_code(EXIT_OK);
	else
	{
		msg_error("noname command", "bad internal call error");
		set_exit_code(EXIT_GENERAL_ERROR);
	}
	return ;
}
