/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:47:03 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/31 17:52:42 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// mallocates buffer if buf is NULL internally needs null check (no gc)
char	*save_getcwd(char *buf, size_t size)
{
	char	*path;

	path = getcwd(buf, size);
	if (path == NULL)
		perror_exit("getcwd failed", EXIT_GENERAL_ERROR);
			// maby not exit here if i dont have permission
	return (path);
}

void	save_chdir(char *new_dir)
{
	if (chdir(new_dir) == -1)
		perror_msg_exit("chdir failed", new_dir, EXIT_GENERAL_ERROR);
	return ;
}

DIR	*save_opendir(char *path)
{
	DIR *dir_stream;

	dir_stream = opendir(path);
	if (dir_stream == NULL)
		perror_msg_exit("opendir", path, EXIT_GENERAL_ERROR);
	return (dir_stream);
}
