/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_o.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:14:38 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 15:56:29 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ptf_o(t_spec *spec)
{
	unsigned int	number;

	number = va_arg(spec->argument, unsigned int);
	spec->string = ptf_ntobase(8, (unsigned)number, spec);
	spec->length += ft_strlen(spec->string);
	if (spec->length < spec->precision)
		spec->length = spec->precision;
	if (number != 0 && spec->alt)
		spec->length += 1;
	if (spec->padding == ' ' && !ptf_write_padding(0, spec))
		return (-1);
	if (number > 0 && spec->alt && !ptf_write_string("0", -1, spec))
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
