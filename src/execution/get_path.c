/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:37 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/12 15:55:34 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// F: Mallocs R: combined_path or NULL
static char	*h_test_path(const char *cmd_name, const char *path)
{
	int		len_path;
	int		len_cmd;
	char	*combined_path;

	len_cmd = ft_strlen(cmd_name);
	while (*path)
	{
		len_path = 0;
		while (path[len_path] != ':' && path[len_path] != '\0')
			len_path++;

		combined_path = ft_calloc(len_path + len_cmd + 2, sizeof(char));
		if (combined_path == NULL)
			return (NULL);
		ft_strlcat(combined_path, path, len_path + len_cmd + 1);
		ft_strlcat(combined_path, "/", len_path + len_cmd + 1);
		ft_strlcat(combined_path, cmd_name, len_path + len_cmd + 1);

		if (access(combined_path, F_OK) == 0)
			return (combined_path);
		path += len_path;
		if (*path == ':')
			path++;
	}
	return (NULL);
}


// F: Mallocs R: combined_path or NULL
char	*get_path_command(const char *cmd_name, char *search_path)
{
	// static const char	*fallback_path
	// 	= "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";


	if (access(cmd_name, F_OK) == 0)
		return (ft_strdup(cmd_name));
	if (search_path == NULL || *search_path == '\0' || cmd_name == NULL)
		return (NULL);
	// 	return (h_test_path(cmd_name, fallback_path));

	return (h_test_path(cmd_name, search_path));
}
