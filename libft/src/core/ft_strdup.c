/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:25:43 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/26 15:01:32 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*duplicate;

	size = ft_strlen(s1);
	duplicate = ft_calloc(1, size + 1);
	if (duplicate)
		return (ft_memcpy(duplicate, s1, size));
	return (NULL);
}
