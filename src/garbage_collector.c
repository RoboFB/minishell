/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:32:15 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/12 19:50:06 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	gc_error(void * memory, char *message)
{
	if (memory)
		free(memory);
	rl_clear_history();
	free(data()->line);
	gc_clear_all();
	ft_fprintf(2, message);
	exit(EXIT_FAILURE);
}

static t_list	**gc_list(t_gc_index index)
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

	if (!memory)
		gc_error(memory, "minishell: heap allocation failed (content)");
	new = ft_lstnew(memory);
	if (!new)
		gc_error(memory, "minishell: heap allocation failed (bookkeeping)");
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
		free(delete->content);
		free(delete);
	}
	*list = NULL;
}

void	gc_clear_all(void)
{
	t_gc_index	index;

	index = 0;
	while (index <= GC_PERSISTENT)
		gc_clear(index++);
	ft_printf("minishell: debug -- garbage collector cleared\n");
}

char	*gc_substr(char const *string, unsigned int start, size_t length)
{
	return (gc_add(ft_substr(string, start, length))->content);
}

char	*gc_strdup(char const *string)
{
	return (gc_add(ft_strdup(string))->content);
}

char	*gc_strjoin(char const *s1, char const *s2)
{
	return (gc_add(ft_strjoin(s1, s2))->content);
}

void	*gc_calloc(size_t count, size_t size)
{
	void	*add;

	add = ft_calloc(count, size);
	gc_add(add);
	return (add);
}


// R: *new_ptr
// sets to zero and copy ptr to new-ptr cuts if new is smaller
void	*gc_realloc(void *ptr, size_t old, size_t new)
{
	void	*new_ptr;

	new_ptr = gc_calloc(new, 1);
	if (ptr)
	{
		if (new > old)
			ft_memcpy(new_ptr, ptr, old);
		else
			ft_memmove(new_ptr, ptr, new);
		
		// gc_remove_one(ptr); //TODO:
		// or just let gc_clear_all handle it 
		// can be get full if called many times
	}
	return (new_ptr);
}
