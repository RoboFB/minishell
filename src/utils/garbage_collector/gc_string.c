/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:32:15 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/04 15:14:03 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_substr(char const *string, unsigned int start, size_t length)
{
	return (gc_add(ft_substr(string, start, length))->content);
}

char	*gc_strdup(char const *string)
{
	if (!string)
		return (NULL);
	return (gc_add(ft_strdup(string))->content);
}

char	*gc_strjoin(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (NULL);
	return (gc_add(ft_strjoin(s1, s2))->content);
}

char	*gc_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	if (!s1 || !s2 || !s3)
		return (NULL);
	return (gc_add(ft_strjoin_3(s1, s2, s3))->content);
}
