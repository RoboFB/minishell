/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:55:59 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/08 22:01:57 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*atomize(t_token **token)
{
	t_token *atom;

	if (!token && !*token)
		return (NULL);
	atom = tok_new("", TOK_ATOM);
	while (*token && !token_is_separator(*token))
	{
		tok_add(*token, &atom->collection);
		*token = (*token)->next;
	}
	atom->collection.tail->next = NULL;
	return (atom);
}

void	contract(t_tokens *list)
{
	t_token		*current;
	t_tokens	new;

	current = list->head;
	list_reset(&new);
	while (current)
	{
		if (token_is_separator(current))
		{
			tok_add(current, &new);
			current = current->next;
		}
		else if (token_is_separator(current->prev)
			&& token_is_separator(current->next)
			&& current->type == TOK_WHITESPACE)
			current = current->next;
		else
		{
			tok_add(atomize(&current), &new);
		}
	}
	list->head = new.head;
	list->tail = new.tail;
	list->size = new.size;
}

void	tokenize(char *line, t_tokens *list)
{
	if (line[0] == '\0')
		return ;
	line_split(line, list);
}
