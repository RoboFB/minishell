/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:14:43 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 15:56:44 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ptf_s(t_spec *spec)
{
	spec->string = va_arg(spec->argument, char *);
	if (!spec->string)
		spec->string = "(null)";
	spec->length = ft_strlen(spec->string);
	if (spec->precision >= 0 && spec->length > spec->precision)
		spec->length = spec->precision;
	spec->padding = ' ';
	if (!ptf_write_padding(0, spec))
		return (-1);
	if (!ptf_write_string(spec->string, spec->precision, spec))
		return (-1);
	if (!ptf_write_padding(1, spec))
		return (-1);
	return (spec->written);
}
