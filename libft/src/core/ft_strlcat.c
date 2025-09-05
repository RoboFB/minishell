/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:26:54 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/24 17:35:44 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	offset;

	index = 0;
	offset = ft_strlen(dst);
	if (dstsize <= offset)
		return (dstsize + ft_strlen(src));
	while (offset + index < dstsize - 1 && src[index])
	{
		dst[offset + index] = src[index];
		index++;
	}
	dst[offset + index] = '\0';
	return (offset + ft_strlen(src));
}
