/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:39:50 by modiepge          #+#    #+#             */
/*   Updated: 2025/08/26 18:11:16 by modiepge         ###   ########.fr       */
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

int	ft_printf(const char *fmt, ...)
{
	va_list	arguments;
	int		written;

	va_start(arguments, fmt);
	written = ft_vfprintf(1, fmt, arguments);
	va_end(arguments);
	return (written);
}
