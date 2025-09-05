/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:22:10 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 00:04:32 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	unsigned int	number;
	char			out[12];
	int				index;

	index = 10;
	number = n;
	ft_memset(out, ' ', 11);
	out[11] = '\0';
	if (n < 0)
		number = -number;
	while (number > 0)
	{
		out[index] = number % 10 + '0';
		number /= 10;
		index--;
	}
	if (n == 0)
		out[index] = '0';
	else if (n < 0)
		out[index] = '-';
	return (ft_strtrim(out, " "));
}
