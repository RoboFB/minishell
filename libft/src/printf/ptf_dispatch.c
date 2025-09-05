/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:02:11 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 13:08:41 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

void	ptf_init_conversions(t_conversion *conversions)
{
	conversions['c'] = ptf_c;
	conversions['s'] = ptf_s;
	conversions['i'] = ptf_id;
	conversions['d'] = ptf_id;
	conversions['u'] = ptf_u;
	conversions['x'] = ptf_x;
	conversions['X'] = ptf_x;
	conversions['p'] = ptf_p;
	conversions['o'] = ptf_o;
	conversions['r'] = ptf_r;
	conversions['b'] = ptf_b;
	conversions['%'] = ptf_percent;
}

void	ptf_init_flags(t_flag *flags)
{
	flags[' '] = ptf_flag_space;
	flags['0'] = ptf_flag_zero;
	flags['.'] = ptf_flag_precision;
	flags['-'] = ptf_flag_left;
	flags['#'] = ptf_flag_alt;
	flags['+'] = ptf_flag_plus;
}
