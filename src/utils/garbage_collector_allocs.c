/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_copy_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:32:15 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/03 12:12:38 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// R: *new_ptr
// sets to zero and copy ptr to new-ptr cuts if new is smaller
void	gc_realloc(void **change_ptr, size_t old, size_t new, size_t size)
{
	void	*new_ptr;

	if (change_ptr == NULL || old == 0 || new == 0 || size == 0 || old == new)
		return ;
	new_ptr = gc_calloc(new, size);
	if (new > old)
		ft_memcpy(new_ptr, *change_ptr, old * size);
	else
		ft_memcpy(new_ptr, *change_ptr, new * size);
	*change_ptr = gc_clear_one(*change_ptr);
	*change_ptr = new_ptr;
	return ;
}

void	*gc_calloc(size_t count, size_t size)
{
	void	*add;

	add = ft_calloc(count, size);
	gc_add(add);
	return (add);
}
