/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:37 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 16:24:59 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in child process
// F: Mallocs R: combined_path or NULL
static char	*h_test_path(const char *cmd_name, const char *path)
{
	int		len_path;
	int		len_cmd;
	char	*full_path;

	len_cmd = ft_strlen(cmd_name);
	full_path = gc_calloc(ft_strlen(path) + len_cmd + 2, sizeof(char));
	while (*path)
	{
		len_path = 0;
		while (path[len_path] != ':' && path[len_path] != '\0')
			len_path++;
		ft_strlcpy(full_path, path, len_path + 1);
		ft_strlcat(full_path, "/", len_path + 2);
		ft_strlcat(full_path, cmd_name, len_path + 2 + len_cmd);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		ft_bzero(full_path, len_path + len_cmd + 2);
		path += len_path;
		if (*path == ':')
			path++;
	}
	return (NULL);
}

// in child process
// uses gc R: combined_path or NULL
char	*get_cmd_path(const char *cmd_name, char *search_path)
{
	if (cmd_name == NULL || *cmd_name == '\0'
		|| (ft_strncmp(cmd_name, ".", 2) == 0)
		|| (ft_strncmp(cmd_name, "..", 3) == 0))
	{
		return (NULL);
	}
	else if (ft_strchr(cmd_name, '/') != NULL)
	{
		return (gc_strdup(cmd_name));
	}
	else if (search_path == NULL || *search_path == '\0')
	{
		return (NULL);
	}
	else
	{
		return (h_test_path(cmd_name, search_path));
	}
}
