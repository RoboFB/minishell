/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_from_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:19:56 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 17:40:31 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
