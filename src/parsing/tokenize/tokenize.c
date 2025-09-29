/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:53:19 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/29 12:38:24 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	this one may need additional work to ensure the incoming line is correctly joined (all literals)
	except for spaces which need to be stripped since quotes are not treated inside variable expansions
*/
int	tok_make_meta_token(char *position, t_tokens *list)
{
	static const t_token_key	symbols[16] = {{">>", TOK_DOUBLE_GREATER},
	{"<<", TOK_DOUBLE_LESS}, {"&&", TOK_AND}, {"||", TOK_OR},
	{"<", TOK_LESS}, {">", TOK_GREATER}, {"&", TOK_AMPERSAND},
	{";", TOK_SEMICOLON}, {"(", TOK_LEFT_PARENTHESIS},
	{")", TOK_RIGHT_PARENTHESIS}, {"*", TOK_WILDCARD},
	{"$", TOK_VARIABLE}, {"|", TOK_PIPE}, {"\"", TOK_DOUBLE_QUOTE},
	{"\'", TOK_QUOTE}, {"\\", TOK_BACKSLASH}};
	int							index;
	size_t						length;

	index = 0;
	length = 0;
	while (index < 16 && ft_strncmp(symbols[index].key, position,
			ft_strlen(symbols[index].key)))
		index++;
	if (index < 16)
	{
		length = ft_strlen(symbols[index].key);
		tok_add(gc_substr(position, 0, length), symbols[index].type, list);
		return (length);
	}
	tok_add(gc_substr(position, 0, 1), TOK_WORD, list);
	return (1);
}

int	tok_make_word_token(char *position, t_tokens *list)
{
	int	length;

	length = 0;
	while (position[length] && !(is_meta_chararacter(position[length])
			|| ft_isspace(position[length])))
		length++;
	tok_add(gc_substr(position, 0, length), TOK_WORD, list);
	return (length);
}

int	tok_make_space_token(char *position, t_tokens *list)
{
	int	length;

	length = 0;
	while (position[length] && ft_isspace(position[length]))
		length++;
	tok_add(gc_substr(position, 0, length), TOK_WHITESPACE, list);
	return (length);
}

void	tokenize(char *line)
{
	if (line[0] == '\0')
		return ;
	gc_mode(GC_LEXING);
	split_line(line, &data()->tokens);
	quote(&data()->tokens);
	expand(&data()->tokens);
	strip_quotes(&data()->tokens);
	join_quotes(&data()->tokens);
	strip_whitespace(&data()->tokens);
	atomize(&data()->tokens);
	tok_debug_display(&data()->tokens);
	list_to_tree();
}

/*
cat test.txt | grep $USER && printf "contains" || printf "does not contain"; printf "mentions of '$USER'\n"
*/