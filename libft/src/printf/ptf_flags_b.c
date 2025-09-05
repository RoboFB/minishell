/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_flags_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:23:52 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 13:08:48 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ptf_flag_space(t_spec *spec)
{
	spec->sign = ' ';
	return (1);
}

int	ptf_flag_alt(t_spec *spec)
{
	spec->alt = 1;
	return (1);
}

int	ptf_flag_plus(t_spec *spec)
{
	spec->sign = '+';
	return (1);
}
