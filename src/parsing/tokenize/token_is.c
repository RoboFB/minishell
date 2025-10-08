/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:27:04 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/07 16:42:41 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_redirect(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOK_DOUBLE_LESS || token->type == TOK_DOUBLE_GREATER
			|| token->type == TOK_GREATER || token->type == TOK_LESS);
}

int	token_is_operator(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOK_PIPE || token->type == TOK_AND
			|| token->type == TOK_OR || token->type == TOK_SEMICOLON);
}

int	token_is_parenthesis(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOK_LEFT_PARENTHESIS
			|| token->type == TOK_RIGHT_PARENTHESIS);
}

int	token_is_separator(t_token *token)
{
	if (!token)
		return (0);
	return (token->is_quoted == 0 && (token_is_operator(token) || token_is_parenthesis(token)));
}

int	is_meta_chararacter(char c)
{
	const char	meta[13] = META_CHARS;
	int			index;

	index = 0;
	while (meta[index] && meta[index] != c)
		index++;
	if (index < 12)
		return (1);
	return (0);
}
