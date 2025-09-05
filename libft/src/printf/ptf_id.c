/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_id.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:14:35 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 15:56:24 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

static int	ptf_flip_number(int number, t_spec *spec)
{
	spec->sign = '-';
	return (-number);
}

int	ptf_id(t_spec *spec)
{
	int	number;

	number = va_arg(spec->argument, int);
	if (number < 0)
		number = ptf_flip_number(number, spec);
	spec->string = ptf_ntobase(10, (unsigned)number, spec);
	spec->length += ft_strlen(spec->string);
	if (spec->length < spec->precision)
		spec->length = spec->precision;
	if (spec->sign)
		spec->length++;
	if (spec->padding == ' ' && !ptf_write_padding(0, spec))
		return (-1);
	if (spec->sign && !ptf_write_character(spec->sign, spec))
		return (-1);
	if (spec->padding == '0' && !ptf_write_padding(0, spec))
		return (-1);
	if (!ptf_write_precision(spec))
		return (-1);
	if (!ptf_write_string(spec->string, spec->length, spec))
		return (-1);
	if (!ptf_write_padding(1, spec))
		return (-1);
	return (spec->written);
}
