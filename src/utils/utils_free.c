/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:18:33 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/08 16:53:23 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// F: free | free split strs and split
void	free_split(char **split)
{
	int	idx;

	if (!split)
		return ;
	idx = 0;
	while (split[idx])
	{
		free(split[idx]);
		idx++;
	}
	free(split);
	return ;
}

// F: Malloc, Free ptr only on success
// R: *new_ptr or NULL Mallocs
// sets to zero and copy ptr to new-ptr cuts if new is smaller
void	*ft_realloc(void *ptr, size_t old, size_t new)
{
	void	*new_ptr;

	new_ptr = ft_calloc(new, 1);
	if (new_ptr == NULL)
		return (NULL);
	if (ptr)
	{
		if (new > old)
			ft_memcpy(new_ptr, ptr, old);
		else
			ft_memmove(new_ptr, ptr, new);
		free(ptr);
	}
	return (new_ptr);
}