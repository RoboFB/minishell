/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:37:30 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 15:56:12 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

static void	ptf_b_width(int number, t_spec *spec)
{
	if (number <= 0xFFFFFF)
		spec->precision = 32;
	if (number <= 0xFFFFF)
		spec->precision = 24;
	if (number <= 0xFFFF)
		spec->precision = 16;
	if (number <= 0xFF)
		spec->precision = 8;
	if (number <= 0xF)
		spec->precision = 4;
}

/*	Outputs the value as binary. Displays "0b" for '#', works as
	normal with precision, unless precision is unset. Then it adds
	leading zeroes to fill 4, 8, 16, 24 or 32 bits.
	Width and alignment work as expected.
*/
int	ptf_b(t_spec *spec)
{
	unsigned int	number;

	number = va_arg(spec->argument, unsigned int);
	spec->string = ptf_ntobase(2, number, spec);
	spec->length += ft_strlen(spec->string);
	if (spec->precision < 0)
		ptf_b_width(number, spec);
	if (spec->alt)
		spec->length += 2;
	if (spec->padding == ' ' && !ptf_write_padding(0, spec))
		return (-1);
	if (spec->alt && !ptf_write_string("0b", -1, spec))
		return (-1);
	if (spec->padding == '0' && !ptf_write_padding(0, spec))
		return (-1);
	if (!ptf_write_precision(spec))
		return (-1);
	if (!ptf_write_string(spec->string, -1, spec))
		return (-1);
	if (!ptf_write_padding(1, spec))
		return (-1);
	return (spec->written);
}
