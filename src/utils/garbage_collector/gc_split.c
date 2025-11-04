/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:23:55 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/23 14:51:22 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	hlp_itemlen(const char *s, char delimiter)
{
	size_t	length;

	length = 0;
	while (s[length] && s[length] != delimiter)
		length++;
	return (length);
}

static char	**hlp_index(const char *s, char delimiter)
{
	size_t	cursor;
	size_t	items;
	char	**index;

	cursor = 0;
	items = 0;
	if (!s)
		return (NULL);
	while (s[cursor])
	{
		while (s[cursor] && s[cursor] == delimiter)
			cursor++;
		if (s[cursor] && s[cursor] != delimiter)
			items++;
		while (s[cursor] && s[cursor] != delimiter)
			cursor++;
	}
	index = gc_calloc(items + 1, sizeof(char *));
	index[items] = NULL;
	return (index);
}

char	**gc_split(const char *s, char c)
{
	size_t	cursor;
	size_t	item;
	char	**index;

	index = hlp_index(s, c);
	cursor = 0;
	item = 0;
	while (s[cursor] && index)
	{
		while (s[cursor] && s[cursor] == c)
			cursor++;
		if (s[cursor] && s[cursor] != c)
		{
			index[item] = gc_substr(s, cursor, hlp_itemlen(&s[cursor], c));
			item++;
		}
		while (s[cursor] && s[cursor] != c)
			cursor++;
	}
	return (index);
}
