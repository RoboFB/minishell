/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector copy 2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:32:15 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/31 18:38:47 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*gc_itoa(int number)
{
	return (gc_add(ft_itoa(number))->content);
}

char *gc_getcwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		perror("getcwd failed");
	gc_add(path);
	return (path);
}

char	*gc_readline(char const *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
		return (NULL);
	else
		return (gc_add(line)->content);
}

char	*gc_get_next_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	else
		return (gc_add(line)->content);
}
