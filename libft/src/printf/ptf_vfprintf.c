/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_vfprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:17:06 by modiepge          #+#    #+#             */
/*   Updated: 2025/07/11 15:53:18 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

static int	ptf_print_arg(t_spec *spec)
{
	static t_conversion	conversions[128];
	static int			init;

	if (!init)
	{
		ptf_init_conversions(conversions);
		init++;
	}
	if (conversions[spec->specifier])
		return (conversions[spec->specifier](spec));
	return (-1);
}

static int	ptf_print_fmt(const char *format, t_spec *spec)
{
	int	length;

	length = 0;
	while (format[length] && format[length] != '%')
		length++;
	return (write(spec->fd, format, length));
}

static int	ptf_read_fmt(const char *format, t_spec *spec)
{
	int	written;
	int	total;

	written = 0;
	total = 0;
	while (format[spec->read])
	{
		if (format[spec->read] != '%')
		{
			written = ptf_print_fmt(&format[spec->read], spec);
			spec->read += written;
		}
		else if (format[spec->read] == '%')
		{
			ptf_read_spec(format, spec);
			written = ptf_print_arg(spec);
		}
		if (written < 0)
			return (written);
		total += written;
	}
	return (total);
}

int	ft_vfprintf(int fd, const char *fmt, va_list arguments)
{
	int		written;
	t_spec	spec;

	ptf_reset_spec(&spec);
	spec.read = 0;
	spec.written = 0;
	spec.fd = fd;
	va_copy(spec.argument, arguments);
	if (!fmt)
		return (0);
	written = ptf_read_fmt(fmt, &spec);
	if (written < 0)
		return (written);
	return (written);
}
