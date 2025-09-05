/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:19:25 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/24 14:10:56 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		cursor;

	cursor = ft_strlen(s);
	while (cursor > 0)
	{
		if (s[cursor] == (char)c)
			return ((char *)&s[cursor]);
		cursor--;
	}
	if (s[0] == (char)c)
		return ((char *)s);
	return (NULL);
}
