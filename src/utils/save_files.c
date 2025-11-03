/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:47:03 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/31 17:51:30 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_dup2(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) == -1)
			perror_exit("dup2 failed", EXIT_GENERAL_ERROR);
	}
	return ;
}

int	save_dup(int copy_fd)
{
	int	new_fd;

	new_fd = dup(copy_fd);
	if (new_fd == -1)
		perror_exit("dup failed", EXIT_GENERAL_ERROR);
	return (new_fd);
}
