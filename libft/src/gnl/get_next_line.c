/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:23:53 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 16:11:09 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gnl.h"

ssize_t	gnl_read(int fd, char **state, char *buffer)
{
	char	*temp;
	ssize_t	bytes;

	while (!gnl_strbreak(*state))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (bytes);
		buffer[bytes] = '\0';
		temp = gnl_assemble(*state, buffer);
		gnl_cleanup(state);
		if (!temp)
			return (-1);
		*state = temp;
	}
	return (1);
}

char	*gnl_pack(char **state)
{
	char	*line;
	char	*clip;
	size_t	cut;
	char	*linebreak;

	if (!state || !*state || !(*state)[0])
		return (NULL);
	linebreak = gnl_strbreak(*state);
	if (linebreak)
		cut = linebreak - *state + 1;
	else
		cut = gnl_strlen(*state);
	line = (char *)malloc(cut + 1);
	if (!line)
		return (NULL);
	line[cut] = '\0';
	while (cut-- > 0)
		line[cut] = (*state)[cut];
	clip = gnl_recycle(state, linebreak);
	*state = clip;
	return (line);
}

char	*gnl_recycle(char **state, char *linebreak)
{
	static char	remains[BUFFER_SIZE];
	size_t		cut;
	size_t		cursor;

	if (linebreak && *state)
	{
		cursor = 0;
		cut = linebreak - *state + 1;
		while ((*state)[cut])
		{
			remains[cursor] = (*state)[cut];
			cursor++;
			cut++;
		}
		remains[cursor] = '\0';
		gnl_cleanup(state);
		return (remains);
	}
	return (gnl_cleanup(state));
}

char	*get_next_line(int fd)
{
	static char	*state;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	state = gnl_assemble(NULL, state);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (gnl_cleanup(&state));
	if (buffer && gnl_read(fd, &state, buffer) < 0)
	{
		gnl_cleanup(&state);
		return (gnl_cleanup(&buffer));
	}
	line = gnl_pack(&state);
	gnl_cleanup(&buffer);
	if (!line)
		gnl_cleanup(&state);
	return (line);
}
