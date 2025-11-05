/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:42:48 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/05 14:07:16 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tok_expansion(t_token *token, char *line, t_tokens *tokens)
{
	t_tokens	*list;
	t_token		*index;

	if (!line)
	{
		tok_delete(&token, tokens);
		return ;
	}
	list = &data()->expansion;
	line_split(line, list);
	index = list->head;
	while (index)
	{
		if (index->type != TOK_WHITESPACE && index->type != TOK_WILDCARD)
			index->is_quoted = TOK_QUOTE;
		index = index->next;
	}
	list_splice(token, tokens, list);
	list_reset(list);
}

bool	expand_logic(t_token *token, t_tokens *tokens)
{
	char	*value;

	if (token->content[0] == '~')
		token->content = get_home(token);
	else if (token->content[1] == '$')
		token->content = gc_itoa(data()->pid);
	else if (token->content[1] == '?')
		token->content = gc_itoa(data()->last_exit_code);
	else
	{
		value = env_get_line_data(&token->content[1]);
		if (!value || !value[0])
		{
			tok_delete(&token, tokens);
			return (false);
		}
		else if (token->is_quoted == TOK_DOUBLE_QUOTE)
			token->content = value;
		else
			tok_expansion(token, value, tokens);
	}
	return (true);
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
		if (token->type == TOK_VARIABLE && token->is_quoted != TOK_QUOTE
			&& (token->content[1] || token->content[0] == '~'))
		{
			if (expand_logic(token, tokens))
				token->type = TOK_WORD;
		}
		if (token)
			token = token->next;
	}
}
