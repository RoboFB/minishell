/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:30:57 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/22 20:22:49 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strip_leftover_vars(t_tokens *tokens)
{
	t_token	*token;

	token = tokens->head;
	while (token)
	{
		if (!token->is_quoted && token->type == TOK_VARIABLE 
			&& ft_strlen(token->content) == 1 && token->next 
			&& token->next->type != TOK_WHITESPACE 
			&& token->next->content[0] != '/')
			tok_delete(&token, tokens);
		if (token)
			token = token->next;
	}
	ft_debugf(1, "lexing: variables stripped\n");
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
	ft_debugf(1, "lexing: whitespace stripped\n");
}
