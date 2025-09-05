/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:28:00 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/24 14:13:28 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	checked;

	checked = 0;
	if (n == 0)
		return (0);
	while (s1[checked] == s2[checked] && checked < n - 1)
	{
		if (!s1[checked] || !s2[checked])
			break ;
		checked++;
	}
	return ((unsigned char)s1[checked] - (unsigned char)s2[checked]);
}
