/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:15:57 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/09 03:28:15 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strip_quotes(t_tokens *tokens)
{
	t_token	*token;

	token = tokens->head;
	while (token)
	{
		if (!token->is_quoted
			&& (token->type == TOK_DOUBLE_QUOTE
			|| token->type == TOK_QUOTE))
		{
			if (token->next && !token->next->is_quoted
				&& (token->next->type == token->type))
			{
				token->content = gc_strdup("");
				token->type = TOK_WORD;
				token->is_quoted = TOK_QUOTE;
			}
			else
				tok_delete(&token, tokens);
		}
		else if (token)
			token = token->next;
	}
	ft_debugf(1, "lexing: quotes stripped\n");
}

void	join_quotes(t_tokens *list)
{
	t_token			*token;
	t_token_type	quote;

	token = list->head;
	while (token)
	{
		if (token->is_quoted && token->next
				&& (token->next->is_quoted || token->next->type == TOK_WORD))
		{
			tok_join(token, token->next, list);
			continue ;
		}
		else if (token->type == TOK_WORD && token->next && token->next->is_quoted)
		{
			quote = token->next->is_quoted;
			tok_join(token, token->next, list);
			token->is_quoted = quote;
			continue ;
		}
		else if ((token->type != TOK_WHITESPACE && !token_is_redirect(token)) && token->next
			&& (token->next->type != TOK_WHITESPACE && !token_is_redirect(token->next)))
		{
			tok_join(token, token->next, list);
			continue ;
		}
		if (token)
			token = token->next;
	}
	ft_debugf(1, "lexing: quote contents joined\n");
}

void	quote(t_tokens *list)
{
	t_token_type	quoted;
	t_token			*token;

	quoted = 0;
	token = list->head;
	while (token)
	{
		if ((token->type == TOK_DOUBLE_QUOTE || token->type == TOK_QUOTE)
			&& (!quoted || quoted == token->type))
		{
			if (!quoted)
				quoted = token->type;
			else if (quoted == token->type)
				quoted = 0;
			token = token->next;
			continue ;
		}
		else if (quoted)
			token->is_quoted = quoted;
		if (token)
			token = token->next;
	}
	if (quoted)
		ft_fprintf(1, "minishell: syntax error (unclosed quote)\n");
	ft_debugf(1, "lexing: quotes marked\n");
}
