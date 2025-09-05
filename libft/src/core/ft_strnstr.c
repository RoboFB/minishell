/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:35:16 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/26 17:37:09 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;

	index = 0;
	if (!needle[index])
		return ((char *)haystack);
	if (*haystack && len < ft_strlen(needle))
		return (NULL);
	while (index <= len - ft_strlen(needle) && haystack[index] != '\0')
	{
		if (ft_strncmp(&haystack[index], needle, ft_strlen(needle)) == 0)
			return ((char *)&haystack[index]);
		index++;
	}
	return (NULL);
}
