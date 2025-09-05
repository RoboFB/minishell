/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:26:11 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/20 16:30:52 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	number;
	char			out[12];
	int				index;

	out[11] = '\0';
	index = 10;
	number = n;
	if (n < 0)
		number = -number;
	while (number > 0)
	{
		out[index] = number % 10 + 48;
		number /= 10;
		index--;
	}
	if (n == 0)
		out[index] = '0';
	else if (n < 0)
		out[index] = '-';
	else
		index++;
	ft_putstr_fd(out + index, fd);
}
