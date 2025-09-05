/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:49:39 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 16:12:30 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

/*	Returns a static, capitalized version of the
	input string (limited by PTF_NUM_BUFFER).
*/
char	*ptf_capitalize(char *number)
{
	static char	out[PTF_NUM_BUFFER + 1];
	int			cursor;

	cursor = 0;
	while (number[cursor] && cursor <= PTF_NUM_BUFFER)
	{
		out[cursor] = (char)ft_toupper((int)number[cursor]);
		cursor++;
	}
	out[cursor] = '\0';
	return (out);
}

/*	Converts a value into the corresponding digit in a base 2, 4,
	8, 10 or 16 system.
*/
char	ptf_convert(unsigned int value, unsigned int base)
{
	static char	*digits[17] = {"", "", "01", "", "0123", "", "", "", "01234567",
		"", "0123456789", "", "", "", "", "", "0123456789abcdef"};

	return (digits[base][value]);
}

/*	Converts a number (nbr) to a string in base 2, 4, 8, 10 or 16.
 */
char	*ptf_ntobase(unsigned int base, unsigned long long nbr, t_spec *spec)
{
	static char			out[PTF_NUM_BUFFER + 1];
	unsigned int		index;
	unsigned long long	number;

	number = nbr;
	out[PTF_NUM_BUFFER] = '\0';
	index = PTF_NUM_BUFFER - 1;
	while (number > 0)
	{
		out[index] = ptf_convert(number % base, base);
		number /= base;
		if (number)
			index--;
	}
	if (nbr == 0)
	{
		out[index] = ptf_convert(0, base);
		if (spec->precision == 0)
			out[index] = '\0';
	}
	return (&out[index]);
}
