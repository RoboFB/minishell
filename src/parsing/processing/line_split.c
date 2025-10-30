/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:05:16 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/30 20:22:17 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tok_variable(char *position, t_tokens *list)
{
	int	length;

	length = 1;
	while (ft_isalnum(position[length]) || position[length] == '_')
		length++;
	if (length == 1)
	{
		if (position[length] == '$')
		{
			tok_add(tok_new(gc_substr(position, 0, length + 1), TOK_VARIABLE), list);
			return (2);
		}
		else if (position[length] == '?')
		{
			tok_add(tok_new(gc_substr(position, 0, length + 1), TOK_VARIABLE), list);
			return (2);
		}
		else
			tok_add(tok_new(gc_substr(position, 0, 1), TOK_VARIABLE), list);
	}
	else
		tok_add(tok_new(gc_substr(position, 0, length), TOK_VARIABLE), list);
	return (length);
}

int	tok_make_meta_token(char *position, t_tokens *list)
{
	static const t_token_key	symbols[18] = {{">>", TOK_DOUBLE_GREATER},
		{"<<", TOK_DOUBLE_LESS}, {"&&", TOK_AND}, {"||", TOK_OR}, {">|", TOK_GREATER},
		{"<", TOK_LESS}, {">", TOK_GREATER}, {"&", TOK_AMPERSAND},
		{";", TOK_SEMICOLON}, {"(", TOK_LEFT_PARENTHESIS},
		{")", TOK_RIGHT_PARENTHESIS}, {"*", TOK_WILDCARD},
		{"$", TOK_VARIABLE}, {"|", TOK_PIPE}, {"\"", TOK_DOUBLE_QUOTE},
		{"\'", TOK_QUOTE}, {"\\", TOK_BACKSLASH}, {"?", TOK_QUESTION}};
	int							index;
	size_t						length;

	index = 0;
	length = 0;
	while (index < 18 && ft_strncmp(symbols[index].key, position,
			ft_strlen(symbols[index].key)))
		index++;
	if (index < 18)
	{
		if (symbols[index].type == TOK_VARIABLE)
			return (tok_variable(position, list));
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
		if (is_meta_chararacter(line[index]) || line[index] == '2')
			index += tok_make_meta_token(&line[index], list);
		else if (ft_isspace(line[index]))
			index += tok_make_space_token(&line[index], list);
		else
			index += tok_make_word_token(&line[index], list);
	}
}
