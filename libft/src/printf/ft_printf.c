/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:39:50 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/23 18:40:11 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ft_fprintf(int fd, const char *fmt, ...)
{
	va_list	arguments;
	int		written;

	va_start(arguments, fmt);
	written = ft_vfprintf(fd, fmt, arguments);
	va_end(arguments);
	return (written);
}

int	ft_debugf(const int level, const char *fmt, ...)
{
	va_list	arguments;
	int		written;

	if (level == DEBUG_MODE || DEBUG_MODE == -1)
	{
		va_start(arguments, fmt);
		written = ft_vfprintf(1, fmt, arguments);
		va_end(arguments);
		return (written);
	}
	return (0);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	arguments;
	int		written;

	va_start(arguments, fmt);
	written = ft_vfprintf(1, fmt, arguments);
	va_end(arguments);
	return (written);
}
