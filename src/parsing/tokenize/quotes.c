/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:15:57 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/28 21:16:09 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strip_quotes(t_tokens *tokens)
{
	t_token	*token;

	token = tokens->head;
	while (token)
	{
		if (!token->is_quoted && (token->type == TOK_DOUBLE_QUOTE
				|| token->type == TOK_QUOTE))
			tok_delete(&token);
		if (token)
			token = token->next;
	}
	ft_debugf(1, "lexing: quotes stripped\n");
}

void	join_quotes(t_tokens *tokens)
{
	t_token			*token;
	t_token_type	quote;

	token = tokens->head;
	while (token)
	{
		if (token->is_quoted && token->next
				&& (token->next->is_quoted || token->next->type == TOK_WORD))
		{
			tok_join(token, token->next);
			continue ;
		}
		else if (token->type == TOK_WORD && token->next && token->next->is_quoted)
		{
			quote = token->next->is_quoted;
			tok_join(token, token->next);
			token->is_quoted = quote;
			continue ;
		}
		if (token)
			token = token->next;
	}
	ft_debugf(1, "lexing: quote contents joined\n");
}

void	quote(t_tokens *tokens)
{
	t_token_type	quoted;
	t_token			*token;

	quoted = 0;
	token = tokens->head;
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
