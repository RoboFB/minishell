/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:57:20 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 15:56:49 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ptf_u(t_spec *spec)
{
	unsigned int	number;

	number = va_arg(spec->argument, unsigned int);
	spec->string = ptf_ntobase(10, (unsigned)number, spec);
	spec->length += ft_strlen(spec->string);
	if (spec->length < spec->precision)
		spec->length = spec->length - ft_strlen(spec->string) + spec->precision;
	if (!ptf_write_padding(0, spec))
		return (-1);
	if (!ptf_write_precision(spec))
		return (-1);
	if (!ptf_write_string(spec->string, -1, spec))
		return (-1);
	if (!ptf_write_padding(1, spec))
		return (-1);
	return (spec->written);
}
