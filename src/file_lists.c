/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:19:56 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/02 16:21:55 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*file_last(t_file *files)
{
	while (files)
	{
		if (!files->next)
			break ;
		files = files->next;
	}
	return (files);
}

t_file	*file_add_front(t_file **files)
{
	t_file	*new;

	gc_mode(GC_PARSING);
	new = (t_file *)gc_calloc(1, sizeof(t_file));
	new->next = NULL;
	new->type = -1;
	new->fd = -1;
	if (!new)
		return (NULL);
	if (!*files)
	{
		new->next = *files;
		*files = new;
		return (new);
	}
	return (new);
}

t_file	*file_add(t_file **files)
{
	t_file	*new;
	t_file	*last;

	gc_mode(GC_PARSING);
	new = (t_file *)gc_calloc(1, sizeof(t_file));
	new->next = NULL;
	new->type = -1;
	new->fd = -1;
	if (!new)
		return (NULL);
	if (!*files)
	{
		*files = new;
		return (new);
	}
	last = file_last(*files);
	last->next = new;
	return (new);
}
