/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:12:26 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 13:06:53 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gnl.h"

char	*gnl_strbreak(const char *str)
{
	size_t	cursor;

	if (!str)
		return (NULL);
	cursor = 0;
	while (str[cursor])
	{
		if (str[cursor] == '\n')
			return ((char *)&str[cursor]);
		cursor++;
	}
	return (NULL);
}

size_t	gnl_strlen(const char *str)
{
	size_t	cursor;

	if (!str)
		return (0);
	cursor = 0;
	while (str[cursor])
		cursor++;
	return (cursor);
}

char	*gnl_assemble(const char *state, const char *add)
{
	char	*assembly;
	size_t	statelen;
	size_t	addlen;

	if (!state && !add)
		return (NULL);
	statelen = gnl_strlen(state);
	addlen = gnl_strlen(add);
	assembly = (char *)malloc(statelen + addlen + 1);
	if (!assembly)
		return (NULL);
	assembly[statelen + addlen] = '\0';
	while (add && addlen-- > 0)
		assembly[statelen + addlen] = add[addlen];
	while (state && statelen-- > 0)
		assembly[statelen] = state[statelen];
	return (assembly);
}

char	*gnl_cleanup(char **pointer)
{
	free(*pointer);
	*pointer = NULL;
	return (NULL);
}
