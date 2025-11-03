/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector init.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:32:15 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/31 18:48:25 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	gc_error(char *message)
{
	perror_exit(message, EXIT_GENERAL_ERROR);
}

t_list	**gc_list(t_gc_index index)
{
	return (&data()->gc_book.lists[index]);
}

void	gc_init(void)
{
	t_gc_index	index;

	index = 0;
	while (index <= GC_PERSISTENT)
		data()->gc_book.lists[index++] = NULL;
}

t_list	*gc_add(void *memory)
{
	t_list	**list;
	t_list	*new;

	if (memory == NULL)
		gc_error("minishell: heap allocation failed of (content)");
	new = ft_lstnew(memory);
	if (new == NULL)
		gc_error("minishell: heap allocation failed of (bookkeeping)");
	list = gc_list(data()->gc_mode);
	if (list)
		ft_lstadd_front(list, new);
	else
		*list = new;
	return (*list);
}

void	gc_mode(t_gc_index mode)
{
	t_gc_index	*index;

	index = &data()->gc_mode;
	*index = mode;
}
