/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:29:15 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/04 16:29:27 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	*interrupted(void)
{
	static bool	interrupted;

	return (&interrupted);
}

int	syntax_error(char *message, char *near)
{
	if (*interrupted())
		return (-1);
	ft_fprintf(2, "minishell: %s", message);
	if (near)
		ft_fprintf(2, " '%s'", near);
	ft_fprintf(2, "\n");
	*interrupted() = true;
	set_exit_code(EXIT_SYNTAX_ERROR);
	return (-1);
}
