/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:11:47 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/12 15:21:03 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *mem, size_t n)
{
	size_t	index;
	char	*destination;

	destination = mem;
	index = 0;
	while (index < n)
	{
		destination[index] = 0;
		index++;
	}
}
