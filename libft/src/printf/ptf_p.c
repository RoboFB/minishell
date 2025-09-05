/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:14:41 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 15:56:34 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ptf_p(t_spec *spec)
{
	uintptr_t	number;

	number = va_arg(spec->argument, uintptr_t);
	spec->string = ptf_ntobase(16, number, spec);
	if (spec->specifier == 'X')
		spec->string = ptf_capitalize(spec->string);
	spec->length += ft_strlen(spec->string) + 2;
	if (spec->padding == ' ' && !ptf_write_padding(0, spec))
		return (-1);
	if (!ptf_write_string("0x", -1, spec))
		return (-1);
	if (!ptf_write_string(spec->string, -1, spec))
		return (-1);
	if (!ptf_write_padding(1, spec))
		return (-1);
	return (spec->written);
}
