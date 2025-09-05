/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:14:46 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 15:57:01 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

static char	*ptf_x_sharp(t_spec *spec)
{
	if (spec->specifier == 'X')
		return ("0X");
	if (spec->specifier == 'x')
		return ("0x");
	return (0);
}

int	ptf_x(t_spec *spec)
{
	unsigned int	number;

	number = va_arg(spec->argument, unsigned int);
	spec->string = ptf_ntobase(16, (unsigned)number, spec);
	if (spec->specifier == 'X')
		spec->string = ptf_capitalize(spec->string);
	spec->length += ft_strlen(spec->string);
	if (spec->length < spec->precision)
		spec->length = spec->precision;
	if (number != 0 && spec->alt)
		spec->length += 2;
	if (spec->padding == ' ' && !ptf_write_padding(0, spec))
		return (-1);
	if (number > 0 && spec->alt && !ptf_write_string(ptf_x_sharp(spec), -1,
			spec))
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
