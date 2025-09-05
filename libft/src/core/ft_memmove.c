/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:19:14 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/27 11:26:09 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	index;
	int		direction;
	char	*destination;
	char	*source;

	if (!dst && !src)
		return (dst);
	destination = dst;
	source = (char *)src;
	index = 0;
	direction = 1;
	if (src < dst)
	{
		index = n - 1;
		direction = -1;
	}
	while (index < n)
	{
		destination[index] = source[index];
		index += direction;
	}
	return (dst);
}
