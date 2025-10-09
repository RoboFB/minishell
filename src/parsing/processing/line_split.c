/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:05:16 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/09 03:03:22 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	tok_make_meta_token(char *position, t_tokens *list)
{
	static const t_token_key	symbols[17] = {{">>", TOK_DOUBLE_GREATER},
		{"<<", TOK_DOUBLE_LESS}, {"&&", TOK_AND}, {"||", TOK_OR},
		{"<", TOK_LESS}, {">", TOK_GREATER}, {"&", TOK_AMPERSAND},
		{";", TOK_SEMICOLON}, {"(", TOK_LEFT_PARENTHESIS},
		{")", TOK_RIGHT_PARENTHESIS}, {"*", TOK_WILDCARD},
		{"$", TOK_VARIABLE}, {"|", TOK_PIPE}, {"\"", TOK_DOUBLE_QUOTE},
		{"\'", TOK_QUOTE}, {"\\", TOK_BACKSLASH}, {"?", TOK_QUESTION}};
	int							index;
	size_t						length;

	index = 0;
	length = 0;
	while (index < 17 && ft_strncmp(symbols[index].key, position,
			ft_strlen(symbols[index].key)))
		index++;
	if (index < 17)
	{
		length = ft_strlen(symbols[index].key);
		tok_add(tok_new(gc_substr(position, 0, length), symbols[index].type), list);
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

void	line_split(char *line, t_tokens *list)
{
	size_t		index;

	index = 0;
	while (line && line[index])
	{
		if (is_meta_chararacter(line[index]))
			index += tok_make_meta_token(&line[index], list);
		else if (ft_isspace(line[index]))
			index += tok_make_space_token(&line[index], list);
		else
			index += tok_make_word_token(&line[index], list);
	}
}
