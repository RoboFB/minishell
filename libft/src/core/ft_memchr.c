/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:08:29 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/24 15:01:03 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*pointer;

	pointer = (unsigned char *)s;
	while (pointer < (const unsigned char *)s + n)
	{
		if (*pointer == (unsigned char)c)
			return ((void *)pointer);
		pointer++;
	}
	return (NULL);
}
