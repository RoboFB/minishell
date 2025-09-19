/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:53:19 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/19 19:41:08 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tok_new(char *content, t_token_type type)
{
	t_token	*new;

	if (!content)
		return (NULL);
	new = (t_token *)gc_calloc(1, sizeof(t_token));
	new->is_quoted = 0;
	new->next = NULL;
	new->prev = NULL;
	new->type = type;
	new->content = content;
	return (new);
}

void	tok_add(char *content, t_token_type type, t_tokens *list)
{
	t_token		*new;
	t_tokens	*tokens;

	new = tok_new(content, type);
	if (!new)
		return ;
	tokens = list;
	if (tokens->head)
	{
		tokens->tail->next = new;
		new->prev = tokens->tail;
		tokens->tail = new;
	}
	else
	{
		tokens->head = new;
		tokens->tail = new;
	}
}

void	tok_delete(t_token *token)
{
	t_tokens	*tokens;

	if (!token)
		return ;
	tokens = &data()->tokens;
	if (token == tokens->head)
		tokens->head = tokens->head->next;
	if (token == tokens->tail)
		tokens->tail = tokens->tail->prev;
	if (token->next)
		token->next->prev = token->prev;
	if (token->prev)
		token->prev->next = token->next;
}

void	tok_join(t_token *first, t_token *second)
{
	if (first && !second)
	{
		first->type = TOK_WORD;
		return ;
	}
	if (first->next != second && second->prev != first)
		return ;
	first->content = gc_strjoin(first->content, second->content);
	first->type = TOK_WORD;
	tok_delete(second);
}

void	tok_debug_display(t_tokens *tokens)
{
	t_token		*token;
	const char	*debug_type[18] = {"TOK_WORD", "TOK_WHITESPACE", "TOK_PIPE",
		"TOK_LEFT_PARENTHESIS", "TOK_RIGHT_PARENTHESIS", "TOK_LESS",
		"TOK_DOUBLE_LESS", "TOK_GREATER", "TOK_DOUBLE_GREATER", "TOK_QUOTE",
		"TOK_DOUBLE_QUOTE", "TOK_AND", "TOK_OR", "TOK_VARIABLE",
		"TOK_WILDCARD", "TOK_AMPERSAND", "TOK_SEMICOLON", "TOK_BACKSLASH"};
	int	arg;
	t_atom *atom;

	token = tokens->head;
	ft_printf("minishell: debug -- display tokens\n");
	while (token)
	{
		if (token->type != TOK_ATOM)
			ft_printf("[%s::%s:%s]\n", token->content, debug_type[token->type], debug_type[token->is_quoted]);
		else
		{
			atom = (t_atom *)token;
			ft_printf("[%s::CMD]\n", atom->command);
			arg = 0;
			while (atom->args[arg + 1])
			{
				ft_printf("[%s::ARG]\n", atom->args[arg + 1]);
				arg++;
			}
		}
		token = token->next;
	}
}

void	tok_reset(t_tokens *tokens)
{
	tokens->head = NULL;
	tokens->tail = NULL;
	tokens->size = 0;
}

int	tok_is_meta_chararacter(char c)
{
	const char	meta[13] = {'|', '&', ';', '(', ')',
		'<', '>', '\"', '\'', '\\', '*', '$', '\0'};
	int			index;

	index = 0;
	while (meta[index] && meta[index] != c)
		index++;
	if (index < 12)
		return (1);
	return (0);
}

/*	this one may need additional work to ensure the incoming line is correctly joined (all literals) 
	except for spaces which need to be stripped since quotes are not treated inside variable expansions
*/
void	tok_expansion(t_token *token, char *line)
{
	t_tokens	*list;
	t_token		*index;

	if (!line)
		return ;
	list = &data()->expansion;
	split_line(line, list);
	index = list->head;
	while (index)
	{
		if (!token->is_quoted && index->type != TOK_WHITESPACE)
			index->is_quoted = TOK_QUOTE;
		if (token->is_quoted)
			index->is_quoted = TOK_QUOTE;
		index = index->next;
	}
	if (token->prev)
		token->prev->next = list->head;
	list->head->prev = token->prev;
	if (token->next)
		token->next->prev = list->tail;
	list->tail->next = token->next;
	list->head = NULL;
	list->tail = NULL;
}

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
	while (position[length] && !(tok_is_meta_chararacter(position[length])
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

/*	Expansion (with quotes accounted for) must occur before joining 
	quoted string contents, otherwise we complicate the logic of joining tokens
*/
void	expand(t_tokens *tokens)
{
	t_token	*token;

	token = tokens->head;
	while (token)
	{
		if (token->type == TOK_VARIABLE && token->is_quoted != TOK_QUOTE)
		{
			if (token->next && token->next->type == TOK_WORD 
					&& token->next->is_quoted == token->is_quoted)
			{
				tok_expansion(token->next,
						env_get_line_data(token->next->content));
				tok_delete(token);
			}
			else if (token->next && token->next->type == TOK_WORD)
				tok_join(token, token->next);
		}
		token = token->next;
	}
	ft_printf("lexing: variables expanded\n");
}

void	strip_whitespace(t_tokens *tokens)
{
	t_token	*token;

	token = tokens->head;
	while (token)
	{
		if (!token->is_quoted && token->type == TOK_WHITESPACE)
			tok_delete(token);
		token = token->next;
	}
	ft_printf("lexing: whitespace stripped\n");
}

void	strip_quotes(t_tokens *tokens)
{
	t_token	*token;

	token = tokens->head;
	while (token)
	{
		if (!token->is_quoted && (token->type == TOK_DOUBLE_QUOTE 
				|| token->type == TOK_QUOTE))
			tok_delete(token);
		token = token->next;
	}
	ft_printf("lexing: quotes stripped\n");
}

void	join_quotes(t_tokens *tokens)
{
	t_token			*token;
	t_token_type	quote;

	token = tokens->head;
	while (token)
	{
		if (token->is_quoted && token->next
				&& (token->next->is_quoted || token->next->type == TOK_WORD))
		{
			tok_join(token, token->next);
			continue ;
		}
		else if (token->type == TOK_WORD && token->next && token->next->is_quoted)
		{
			quote = token->next->is_quoted;
			tok_join(token, token->next);
			token->is_quoted = quote;
			continue ;
		}
		token = token->next;
	}
	ft_printf("lexing: quote contents joined\n");
}

void	quote(t_tokens *tokens)
{
	t_token_type	quoted;
	t_token			*token;

	quoted = 0;
	token = tokens->head;
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
		token = token->next;
	}
	if (quoted)
		ft_printf("minishell: syntax error (unclosed quote)\n");
	ft_printf("lexing: quotes marked\n");
}

void	split_line(char *line, t_tokens *list)
{
	size_t		index;

	index = 0;
	while (line && line[index])
	{
		if (tok_is_meta_chararacter(line[index]))
			index += tok_make_meta_token(&line[index], list);
		else if (ft_isspace(line[index]))
			index += tok_make_space_token(&line[index], list);
		else
			index += tok_make_word_token(&line[index], list);
	}
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
	tok_reset(&data()->tokens);
}

/*
cat test.txt | grep $USER && printf "contains" || printf "does not contain"; printf "mentions of '$USER'\n"
*/