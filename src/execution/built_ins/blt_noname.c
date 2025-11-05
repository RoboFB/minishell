/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_noname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:27:01 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 15:47:28 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	blt_noname(t_expression *command)
{
	if (command->name == NULL)
		set_exit_code(EXIT_OK);
	else
	{
		msg_error("programming error", "bad internal call error in noname");
		set_exit_code(EXIT_GENERAL_ERROR);
	}
	return ;
}
