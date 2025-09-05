/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_percent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:14:29 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 13:09:09 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ptf_percent(t_spec *spec)
{
	spec->length = 1;
	spec->padding = ' ';
	if (!ptf_write_padding(0, spec))
		return (-1);
	if (!ptf_write_character('%', spec))
		return (-1);
	if (!ptf_write_padding(1, spec))
		return (-1);
	return (spec->written);
}
