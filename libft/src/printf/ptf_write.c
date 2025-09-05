/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:36:51 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 13:09:33 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

/*	Will write up to max_length characters of a string. If max_length is
	negative (-1), the full string is written. If the write() call fails, this
	function returns false. Otherwise, spec->written is incremented and true is
	returned.
*/
int	ptf_write_string(char *str, int max_length, t_spec *spec)
{
	int	length;
	int	written;

	length = ft_strlen(str);
	if (length > max_length && max_length >= 0)
		length = max_length;
	written = write(spec->fd, str, length);
	if (written < 0)
		return (0);
	spec->written += written;
	return (1);
}

int	ptf_write_character(char c, t_spec *spec)
{
	int	written;

	written = write(spec->fd, &c, 1);
	if (written < 0)
		return (0);
	spec->written += written;
	return (1);
}

int	ptf_write_padding(int left, t_spec *spec)
{
	int	written;

	written = 0;
	if (left == spec->left && spec->length < spec->width)
	{
		if (spec->width >= 0)
			written = ptf_padding(spec->padding, spec->width - spec->length,
					spec);
		if (written < 0)
			return (0);
		spec->written += written;
		return (1);
	}
	return (1);
}

int	ptf_write_precision(t_spec *spec)
{
	int	written;

	written = 0;
	if ((int)ft_strlen(spec->string) < spec->precision)
	{
		if (spec->precision >= 0)
		{
			written = ptf_padding('0', spec->precision
					- ft_strlen(spec->string), spec);
		}
		if (written < 0)
			return (0);
		spec->written += written;
		return (1);
	}
	return (1);
}
