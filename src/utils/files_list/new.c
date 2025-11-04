/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:19:56 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 17:40:42 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*file_make(void)
{
	t_file	*new;

	gc_mode(GC_TEMPORARY);
	new = (t_file *)gc_calloc(1, sizeof(t_file));
	new->type = NOT_SET;
	new->path = NULL;
	new->fd = -1;
	new->next = NULL;
	return (new);
}

// next is set to NULL and fd to -1 of input
t_file	*file_dup_values(t_file *input)
{
	t_file	*new;

	gc_mode(GC_TEMPORARY);
	new = (t_file *)gc_calloc(1, sizeof(t_file));
	new->type = input->type;
	new->path = input->path;
	new->fd = save_dup(input->fd);
	new->next = NULL;
	return (new);
}
