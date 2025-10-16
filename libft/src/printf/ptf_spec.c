/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_spec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:01:37 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/16 18:00:32 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

/*	Reads a conversion specification by either traversing however many digits
	there are to read, or advancing va_list by one, in case of '*'.
*/
static int	ptf_atou(const char *str, t_spec *spec)
{
	int	cursor;
	int	result;

	cursor = 0;
	result = 0;
	if (str[cursor] == '*')
	{
		result = va_arg(spec->argument, int);
		spec->read++;
		if (result < 0)
		{
			spec->left = 1;
			result = -result;
		}
		while (ft_isdigit(str[cursor]))
			spec->read++;
		return (result);
	}
	while (ft_isdigit(str[cursor]))
	{
		result = result * 10 + (str[cursor] - 48);
		cursor++;
		spec->read++;
	}
	return (result);
}

/*	Initializes a dispatch table to handle various conversion flags once,
	then checks if a flag is handled. If so, it returns a positive int,
	else: 0
*/
static int	ptf_set_flag(char flag, t_spec *spec)
{
	static t_flag	flags[128];
	static int		init;
	int				index;

	index = (int)flag;
	if (!init)
	{
		ptf_init_flags(flags);
		init++;
	}
	if (flags[index])
		return (flags[index](spec));
	return (0);
}

/*	Resets struct to initial state for the current conversion string to be
	parsed. Written and read bytes remain.
*/
int	ptf_reset_spec(t_spec *spec)
{
	spec->specifier = '\0';
	spec->string = NULL;
	spec->left = 0;
	spec->width = -1;
	spec->precision = -1;
	spec->padding = ' ';
	spec->sign = '\0';
	spec->alt = 0;
	spec->length = 0;
	spec->written = 0;
	if (!spec->fd)
		spec->fd = 1;
	return (1);
}

/*	Parses the conversion string under the assumption of:
	%[flags][width][.precision][specifier] duplicates and malformed
	width/precision should be handled by the respective handlers.
*/
int	ptf_read_spec(const char *fmt, t_spec *spec)
{
	ptf_reset_spec(spec);
	if (fmt[spec->read])
	{
		if (fmt[spec->read] == '%')
			spec->read++;
		while (fmt[spec->read] != '.' && ptf_set_flag(fmt[spec->read], spec))
			spec->read++;
		if ((ft_isdigit(fmt[spec->read]) && fmt[spec->read] != '0')
			|| fmt[spec->read] == '*')
			spec->width = ptf_atou(&fmt[spec->read], spec);
		if ((fmt[spec->read] == '.' && ptf_set_flag(fmt[spec->read], spec))
			|| fmt[spec->read] == '*')
		{
			spec->read++;
			spec->precision = ptf_atou(&fmt[spec->read], spec);
		}
		if (ft_isalpha(fmt[spec->read]) || fmt[spec->read] == '%')
		{
			spec->specifier = fmt[spec->read++];
			return (0);
		}
		spec->read++;
	}
	return (0);
}
