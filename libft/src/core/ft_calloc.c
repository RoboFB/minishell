/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:50:55 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/24 13:30:22 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;

	if (count == 0 || size == 0)
	{
		memory = malloc(0);
		return (memory);
	}
	if (count < SIZE_MAX / size)
	{
		memory = malloc(count * size);
		if (memory)
		{
			return (ft_memset(memory, 0, size * count));
		}
	}
	return (NULL);
}
