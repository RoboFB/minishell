/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:45:40 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/05 12:18:01 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*list_skip_whitespace(t_token *token)
{
	if (!token)
		return (NULL);
	while (token && token->is_quoted == 0 && token->type == TOK_WHITESPACE)
		token = token->next;
	return (token);
}

void	list_reset(t_tokens *tokens)
{
	tokens->head = NULL;
	tokens->tail = NULL;
	tokens->size = 0;
}

bool	list_trim(t_tokens *list)
{
	if (list->head)
		list->head->prev = NULL;
	if (list->tail)
		list->tail->next = NULL;
	if (list->head && list->tail)
		return (true);
	return (false);
}

t_token	*list_splice(t_token *token, t_tokens *list, t_tokens *new)
{
	if (token->prev)
		token->prev->next = new->head;
	else
		list->head = new->head;
	if (new->head)
		new->head->prev = token->prev;
	if (token->next)
		token->next->prev = new->tail;
	else
		list->tail = new->tail;
	if (new->tail)
		new->tail->next = token->next;
	return (new->head);
}
