/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:36:10 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/24 14:02:50 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	index;
	char	*destination;
	char	*source;

	if (!dst && !src)
		return (dst);
	destination = dst;
	source = (char *)src;
	index = 0;
	while (index < n)
	{
		destination[index] = source[index];
		index++;
	}
	return (dst);
}
