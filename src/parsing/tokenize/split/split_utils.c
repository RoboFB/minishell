/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:02:53 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/05 14:42:33 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const t_token_key	*tok_identify_meta_token(char *position)
{
	static const t_token_key	symbols[19] = {{">>", TOK_DOUBLE_GREATER},
	{"<<", TOK_DOUBLE_LESS}, {"&&", TOK_AND}, {"||", TOK_OR},
	{">|", TOK_GREATER}, {"<", TOK_LESS}, {">", TOK_GREATER},
	{"&", TOK_AMPERSAND}, {";", TOK_SEMICOLON}, {"(", TOK_LEFT_PARENTHESIS},
	{")", TOK_RIGHT_PARENTHESIS}, {"*", TOK_WILDCARD}, {"$", TOK_VARIABLE},
	{"~", TOK_VARIABLE}, {"|", TOK_PIPE}, {"\"", TOK_DOUBLE_QUOTE},
	{"\'", TOK_QUOTE}, {"\\", TOK_BACKSLASH}, {"?", TOK_QUESTION}};
	int							index;

	index = 0;
	while (index < 19 && ft_strncmp(symbols[index].key, position,
			ft_strlen(symbols[index].key)))
		index++;
	if (index < 19)
		return (&symbols[index]);
	return (NULL);
}

int	tok_make_meta_token(char *position, t_tokens *list)
{
	size_t						length;
	t_token_key					*symbol;

	symbol = (t_token_key *)tok_identify_meta_token(position);
	length = 0;
	if (symbol)
	{
		if (symbol->type == TOK_VARIABLE && position[0] != '~')
			return (tok_variable(position, list));
		else if (symbol->type == TOK_VARIABLE)
			return (tok_home(position, list));
		length = ft_strlen(symbol->key);
		tok_add(tok_new(gc_substr(position, 0, length), symbol->type),
			list);
		return (length);
	}
	tok_add(tok_new(gc_substr(position, 0, 1), TOK_WORD), list);
	return (1);
}

int	tok_make_word_token(char *position, t_tokens *list)
{
	int	length;

	length = 0;
	while (position[length] && !(is_meta_chararacter(position[length])
			|| ft_isspace(position[length])))
		length++;
	tok_add(tok_new(gc_substr(position, 0, length), TOK_WORD), list);
	return (length);
}

int	tok_make_space_token(char *position, t_tokens *list)
{
	int	length;

	length = 0;
	while (position[length] && ft_isspace(position[length]))
		length++;
	tok_add(tok_new(gc_substr(position, 0, length), TOK_WHITESPACE), list);
	return (length);
}
