/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:19:22 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/24 16:38:24 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	cursor;

	cursor = 0;
	while (s[cursor])
	{
		if (s[cursor] == (char)c)
			return ((char *)&s[cursor]);
		cursor++;
	}
	if ((char)c == '\0')
		return ((char *)&s[cursor]);
	return (NULL);
}
