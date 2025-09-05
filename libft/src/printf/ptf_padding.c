/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:40:39 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 16:14:28 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

/*	Returns a 128 character buffer of either ' ' or '0'. Default is ' ' to
	prevent accidental read errors e. g. write(1, NULL, 128).
*/
static char	*ptf_buffer(char c)
{
	char		*out;
	static char	*zero = "000000000000000000000000000000000000000000000000000000\
00000000000000000000000000000000000000000000000000000000000000000000000000";
	static char	*space = "                                                     \
                                                                           ";

	out = space;
	if (c == '0')
		out = zero;
	return (out);
}

/*	Writes however many characters of either '0' or ' ' are needed in
	128 byte chunks.

	Returns the total bytes written, or--in case of error--negative one (-1)
*/
int	ptf_padding(char c, int length, t_spec *spec)
{
	int	written;
	int	writing;
	int	last;

	written = 0;
	while (written < length)
	{
		writing = 128;
		if (length - written < 128)
			writing = length - written;
		last = write(spec->fd, ptf_buffer(c), writing);
		if (last < 0)
			return (last);
		written += last;
	}
	return (written);
}
