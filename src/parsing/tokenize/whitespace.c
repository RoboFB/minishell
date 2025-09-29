/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:30:57 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/28 22:31:21 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strip_whitespace(t_tokens *tokens)
{
	t_token	*token;

	token = tokens->head;
	while (token)
	{
		if (!token->is_quoted && token->type == TOK_WHITESPACE)
			tok_delete(&token);
		if (token)
			token = token->next;
	}
	ft_debugf(1, "lexing: whitespace stripped\n");
}
