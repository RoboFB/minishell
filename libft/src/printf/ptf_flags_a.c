/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_flags_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:23:52 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 13:08:44 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ptf_flag_left(t_spec *spec)
{
	spec->left = 1;
	spec->padding = ' ';
	return (1);
}

int	ptf_flag_zero(t_spec *spec)
{
	if (!spec->left)
		spec->padding = '0';
	return (1);
}

int	ptf_flag_precision(t_spec *spec)
{
	if (spec->padding == '0')
		spec->padding = ' ';
	spec->precision = 0;
	return (1);
}
