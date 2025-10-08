/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:42:48 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/07 17:36:48 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tok_expansion(t_token *token, char *line)
{
	t_tokens	*list;
	t_token		*index;

	if (!line)
		return ;
	list = &data()->expansion;
	line_split(line, list);
	index = list->head;
	while (index)
	{
		if (!token->is_quoted && index->type != TOK_WHITESPACE)
			index->is_quoted = TOK_QUOTE;
		if (token->is_quoted)
			index->is_quoted = TOK_QUOTE;
		index = index->next;
	}
	if (token->prev)
		token->prev->next = list->head;
	list->head->prev = token->prev;
	if (token->next)
		token->next->prev = list->tail;
	list->tail->next = token->next;
	list->head = NULL;
	list->tail = NULL;
}

/*	Expansion (with quotes accounted for) must occur before joining
	quoted string contents, otherwise we complicate the logic of joining tokens
*/
void	expand(t_tokens *tokens)
{
	t_token	*token;

	token = tokens->head;
	while (token)
	{
		if (token->type == TOK_VARIABLE && token->is_quoted != TOK_QUOTE)
		{
			if (token->next && token->next->type == TOK_WORD
					&& token->next->is_quoted == token->is_quoted)
			{
				tok_expansion(token->next,
						env_get_line_data(token->next->content));
				tok_delete(&token, tokens);
			}
			else if (token->next && token->next->type == TOK_WORD)
				tok_join(token, token->next, tokens);
		}
		token = token->next;
	}
	ft_debugf(1, "lexing: variables expanded\n");
}
