/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:26:25 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/31 11:35:27 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hlp_isspace(int c)
{
	return ((9 <= c && c <= 13) || c == 32);
}

static int	hlp_issign(int c)
{
	return (c == '-' || c == '+');
}

int	ft_atoi(const char *str)
{
	size_t			index;
	int				sign;
	unsigned int	result;

	index = 0;
	sign = 1;
	result = 0;
	while (hlp_isspace(str[index]))
	{
		index++;
	}
	if (hlp_issign(str[index]))
	{
		if (str[index] == '-')
			sign *= -1;
		index++;
	}
	while (ft_isdigit(str[index]))
	{
		result = result * 10 + (str[index] - 48) * sign;
		index++;
	}
	return ((int)result);
}
