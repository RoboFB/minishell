/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:15:57 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/05 12:18:53 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	join_quotes_logic(t_token *token, t_tokens *list)
{
	t_token_type	quote;

	if (token->is_quoted && token->next && (token->next->is_quoted
			|| token->next->type == TOK_WORD))
	{
		tok_join(token, token->next, list);
		return (false);
	}
	else if (token->type == TOK_WORD && token->next
		&& token->next->is_quoted)
	{
		quote = token->next->is_quoted;
		tok_join(token, token->next, list);
		token->is_quoted = quote;
		return (false);
	}
	else if (token && token->next
		&& !token_is_space(token) && !token_is_space(token->next)
		&& !token_is_redirect(token) && !token_is_redirect(token->next))
	{
		tok_join(token, token->next, list);
		return (false);
	}
	return (true);
}

void	join_quotes(t_tokens *list)
{
	t_token			*token;

	token = list->head;
	while (token)
	{
		if (join_quotes_logic(token, list) && token)
			token = token->next;
	}
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
		syntax_error("syntax error (unclosed quote)", NULL);
}
