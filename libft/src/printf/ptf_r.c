/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:14:46 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 15:56:39 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

static void	ptf_check_base(t_spec *spec)
{
	if ((spec->precision < 0 || spec->precision > 16) || !ptf_convert(0,
			spec->precision))
		spec->precision = 2;
}

/*	Outputs the buffer passed as a void * byte by byte, separated by spaces.
	base for conversion is dictated by precision (2, 4, 8, 10 or 16).
	By default, the buffer is read until a NULL-bytes is encountered. Width may
	extend this limit. Both are at risk of segfault depending on the
	input argument.
*/
int	ptf_r(t_spec *spec)
{
	char	*buffer;
	int		cursor;
	int		byte_len;
	int		written;

	cursor = 0;
	ptf_check_base(spec);
	byte_len = ft_strlen(ptf_ntobase(spec->precision, 255, spec));
	buffer = (char *)va_arg(spec->argument, void *);
	while (cursor < spec->width || (spec->width < 0 && buffer[cursor]))
	{
		written = 0;
		if (cursor > 0 && !ptf_write_character(' ', spec))
			return (-1);
		spec->string = ptf_ntobase(spec->precision, buffer[cursor], spec);
		if ((int)ft_strlen(spec->string) < byte_len)
			written = ptf_padding('0', byte_len - ft_strlen(spec->string),
					spec);
		ptf_write_string(spec->string, -1, spec);
		if (written < 0)
			return (written);
		spec->written += written;
		cursor++;
	}
	return (spec->written);
}
