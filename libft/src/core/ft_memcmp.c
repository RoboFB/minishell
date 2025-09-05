/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:21:27 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/24 15:06:38 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				index;
	const unsigned char	*pointer1;
	const unsigned char	*pointer2;

	index = 0;
	if (n == 0)
		return (0);
	pointer1 = (const unsigned char *)s1;
	pointer2 = (const unsigned char *)s2;
	while (pointer1[index] == pointer2[index] && index < n - 1)
		index++;
	return (pointer1[index] - pointer2[index]);
}
