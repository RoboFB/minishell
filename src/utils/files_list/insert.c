/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:19:56 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 17:39:45 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_file	*file_get_last(t_file *start)
{
	t_file	*head;

	head = start;
	while (head && head->next)
		head = head->next;
	return (head);
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
