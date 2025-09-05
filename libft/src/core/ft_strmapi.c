/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:57:44 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/24 13:44:17 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*out;
	unsigned int	index;

	out = malloc(ft_strlen(s) + 1);
	if (!out)
		return (out);
	index = 0;
	while (s[index] != '\0')
	{
		out[index] = f(index, s[index]);
		index++;
	}
	out[index] = '\0';
	return (out);
}
