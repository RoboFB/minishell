/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:26:25 by modiepge          #+#    #+#             */
/*   Updated: 2025/08/26 16:26:33 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hlp_charset(int c, int base)
{
	const char	*lowercase = "0123456789abcdef";
	const char	*uppercase = "0123456789ABCDEF";
	int			value;

	value = 0;
	while (value < base && lowercase[value] != c && uppercase[value] != c)
		value++;
	if (value == base)
		return (-1);
	return (value);
}

unsigned int	ft_atou_base(const char *str, int base)
{
	size_t			index;
	unsigned int	result;

	index = 0;
	result = 0;
	if (base > 16 || base < 2)
		return (0);
	while (ft_isspace(str[index]))
		index++;
	while (hlp_charset(str[index], base) >= 0)
	{
		result = result * base + hlp_charset(str[index], base);
		index++;
	}
	return (result);
}
