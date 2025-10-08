/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:32:15 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/01 15:16:19 by rgohrig          ###   ########.fr       */
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
		if (delete->content)
			free(delete->content);
		free(delete);
	}
	*list = NULL;
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

char	*gc_substr(char const *string, unsigned int start, size_t length)
{
	return (gc_add(ft_substr(string, start, length))->content);
}

char	*gc_strdup(char const *string)
{
	if (!string)
		return (NULL);
	return (gc_add(ft_strdup(string))->content);
}

char	*gc_strjoin(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (NULL);
	return (gc_add(ft_strjoin(s1, s2))->content);
}

void	*gc_calloc(size_t count, size_t size)
{
	void	*add;

	add = ft_calloc(count, size);
	gc_add(add);
	return (add);
}

char *gc_getcwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		perror("getcwd failed");
	gc_add(path);
	return (path);
}

char	*gc_readline(char const *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
		return (NULL);
	else
		return (gc_add(line)->content);
}

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
	*change_ptr = new_ptr;
	// gc_remove_one(ptr); //TODO:
	// or just let gc_clear_all handle it
	// can be get full if called many times
	return ;
}

// removes one entry from gc use gc_mode
void *gc_remove_one(void *remove_ptr)
{
	// TODO: Implement
	(void)remove_ptr;

	return (NULL);
}