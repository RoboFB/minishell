/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:58:34 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/24 13:38:47 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;

	if (ft_strlen(s1) > SIZE_MAX - ft_strlen(s2))
		return (NULL);
	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join)
	{
		ft_bzero(join, ft_strlen(s1) + ft_strlen(s2) + 1);
		ft_memcpy(join, s1, ft_strlen(s1));
		ft_memcpy(join + ft_strlen(s1), s2, ft_strlen(s2));
	}
	return (join);
}

char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	if (s1_len > SIZE_MAX - s2_len - s3_len)
		return (NULL);
	join = ft_calloc(s1_len + s2_len + s3_len + 1, sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_memcpy(join, s1, s1_len);
	ft_memcpy(join + s1_len, s2, s2_len);
	ft_memcpy(join + s1_len + s2_len, s3, s3_len);
	return (join);
}
