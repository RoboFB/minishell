/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:17:26 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/24 15:42:00 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hlp_match(char const c, char const *set)
{
	size_t	cursor;

	cursor = 0;
	while (set[cursor] && set[cursor] != c)
		cursor++;
	if (cursor < ft_strlen(set))
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	length;

	start = 0;
	length = ft_strlen(s1) - 1;
	while (s1[start] && hlp_match(s1[start], set))
		start++;
	while (length + 1 > start && hlp_match(s1[length], set))
		length--;
	return (ft_substr(s1, start, length - start + 1));
}
