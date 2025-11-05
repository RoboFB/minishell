/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:13:57 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/05 12:17:43 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tok_new(char *content, t_token_type type)
{
	t_token	*new;

	if (!content)
		return (NULL);
	new = (t_token *)gc_calloc(1, sizeof(t_token));
	new->is_quoted = 0;
	new->next = NULL;
	new->prev = NULL;
	new->type = type;
	new->content = content;
	new->id = 0;
	new->collection.head = NULL;
	new->collection.tail = NULL;
	new->collection.size = 0;
	return (new);
}

void	tok_add(t_token *new, t_tokens *list)
{
	if (!new || !list)
		return ;
	if (list->head)
	{
		list->tail->next = new;
		new->prev = list->tail;
		list->tail = new;
	}
	else
	{
		list->head = new;
		list->tail = new;
	}
}

void	tok_delete(t_token **token, t_tokens *list)
{
	t_tokens	*tokens;

	if (!token)
		return ;
	tokens = list;
	if (*token == tokens->head)
		tokens->head = tokens->head->next;
	if (*token == tokens->tail)
		tokens->tail = tokens->tail->prev;
	if ((*token)->next)
		(*token)->next->prev = (*token)->prev;
	if ((*token)->prev)
		(*token)->prev->next = (*token)->next;
	*token = (*token)->next;
}

void	tok_join(t_token *first, t_token *second, t_tokens *list)
{
	if (first && !second)
	{
		first->type = TOK_WORD;
		return ;
	}
	if (first->next != second && second->prev != first)
		return ;
	first->content = gc_strjoin(first->content, second->content);
	if ((first->type == TOK_WILDCARD && !first->is_quoted)
		|| (second->type == TOK_WILDCARD && !second->is_quoted))
	{
		first->type = TOK_WILDCARD;
		first->is_quoted = 0;
	}
	else
		first->type = TOK_WORD;
	tok_delete(&second, list);
}
