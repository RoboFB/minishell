/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:57:11 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 15:56:19 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ptf_c(t_spec *spec)
{
	spec->length = 1;
	spec->padding = ' ';
	if (!ptf_write_padding(0, spec))
		return (-1);
	if (!ptf_write_character((char)va_arg(spec->argument, int), spec))
		return (-1);
	if (!ptf_write_padding(1, spec))
		return (-1);
	return (spec->written);
}
