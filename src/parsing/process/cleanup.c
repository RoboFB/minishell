/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:30:57 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/06 15:40:48 by modiepge         ###   ########.fr       */
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
}

void	strip_leftover_vars(t_tokens *tokens)
{
	t_token	*token;

	token = tokens->head;
	while (token)
	{
		if (!token->is_quoted
			&& token->type == TOK_VARIABLE
			&& ft_strlen(token->content) == 1
			&& token->content[0] != '~'
			&& token->next
			&& token->next->type != TOK_WHITESPACE
			&& token->next->content[0] != '/')
			tok_delete(&token, tokens);
		if (token)
			token = token->next;
	}
}

void	strip_whitespace(t_tokens *tokens)
{
	t_token	*token;

	token = tokens->head;
	while (token)
	{
		if (!token->is_quoted && token->type == TOK_WHITESPACE)
			tok_delete(&token, tokens);
		if (token)
			token = token->next;
	}
}
