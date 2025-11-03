/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_clear.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:32:15 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/03 12:43:38 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gc_clear(t_gc_index index)
{
	t_list	*current;
	t_list	*delete;
	t_list	**list;

	list = gc_list(index);
	if (!list)
		return ;
	current = *list;
	delete = NULL;
	while (current)
	{
		delete = current;
		current = current->next;
		if (delete->content)
			free(delete->content);
		free(delete);
	}
	*list = NULL;
}

// content_ptr is the pointer to the value | null it after the call !
void	*gc_clear_one(void *content_ptr)
{
	t_list	*current;
	t_list	**list;

	list = gc_list(data()->gc_mode);
	if (!list)
		return (NULL);
	current = *list;
	while (current)
	{
		if (current->content == content_ptr)
		{
			free(current->content);
			current->content = NULL;
			return (NULL);
		}
		current = current->next;
	}
	return (NULL);
}

void	gc_clear_temporary(void)
{
	t_gc_index	index;

	index = 0;
	while (index < GC_PERSISTENT)
		gc_clear(index++);
	list_reset(&data()->tokens);
	data()->tree_root = NULL;
	ft_debugf(1, "minishell: debug -- temporary data cleared\n");
}

void	gc_clear_all(void)
{
	t_gc_index	index;

	index = 0;
	while (index <= GC_PERSISTENT)
		gc_clear(index++);
	ft_debugf(1, "minishell: debug -- garbage collector cleared\n");
}
