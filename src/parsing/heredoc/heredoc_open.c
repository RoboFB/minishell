/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:33:18 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/04 18:43:58 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_open(const char *path, int flags, int permissions)
{
	int	fd;

	fd = -1;
	fd = open(path, flags, permissions);
	if (fd == -1)
	{
		ft_fprintf(2, "minishell: %s: %s\n", strerror(errno), path);
		set_exit_code(EXIT_GENERAL_ERROR);
	}
	return (fd);
}
