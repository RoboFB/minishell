/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:19:56 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/31 17:05:11 by rgohrig          ###   ########.fr       */
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
	
	// input->fd = -1;

	return (new);
}

t_file	*file_get_last(t_file *start)
{
	t_file	*head;

	head = start;
	while (head && head->next)
		head = head->next;
	return (head);
}

// use address of a pointer
void	file_append_front(t_file **start_ptr, t_file *add_file)
{
	if (!start_ptr || !add_file)
		return ;
	if (*start_ptr == NULL)
	{
		*start_ptr = add_file;
	}
	else
	{
		add_file->next = *start_ptr;
		*start_ptr = add_file;
	}
	return ;
}

// use address of a pointer
void	file_append_back(t_file **start_ptr, t_file *add_file)
{
	if (!start_ptr || !add_file)
		return ;
	if (*start_ptr == NULL)
	{
		*start_ptr = add_file;
	}
	else
	{
		file_get_last(*start_ptr)->next = add_file;
	}
	return ;
}

// use address of a pointer R: the new element
t_file	*file_add_front(t_file **start_ptr)
{
	t_file	*new;

	new = file_make();
	file_append_front(start_ptr, new);
	return (new);
}

// use address of a pointer R: the new element
t_file	*file_add_back(t_file **start_ptr)
{
	t_file	*new;

	new = file_make();
	file_append_back(start_ptr, new);
	return (new);
}

t_file	*file_pop_front(t_file **start_ptr)
{
	t_file	*out;

	if (!start_ptr || !*start_ptr)
		return (NULL);
	out = *start_ptr;
	*start_ptr = out->next;
	out->next = NULL;
	return (out);
}

t_file	*file_pop_back(t_file **start_ptr)
{
	t_file	*head;
	t_file	*out;
	t_file	*previous_ptr;

	if (!start_ptr || !*start_ptr)
		return (NULL);
	head = *start_ptr;
	if (head->next == NULL)
	{
		out = head;
		*start_ptr = NULL;
		return (out);
	}
	while (head->next)
	{
		previous_ptr = head;
		head = head->next;
	}
	out = previous_ptr->next;
	previous_ptr->next = NULL;
	return (out);
}
