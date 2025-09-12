/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:53:19 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/12 17:39:05 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tok_new(char *content, t_token_type type)
{
	t_token	*new;

	if (!content)
		return (NULL);
	new = (t_token *)gc_calloc(1, sizeof(t_token));	
	new->next = NULL;
	new->prev = NULL;
	new->type = type;
	new->content = content;
	return (new);
}

void	tok_add(char *content, t_token_type type)
{
	t_token		*new;
	t_tokens	*tokens;

	new = tok_new(content, type);
	if (!new)
		return ;
	tokens = &data()->tokens;
	if (tokens->head)
	{
		tokens->tail->next = new;
		new->prev = tokens->tail;
		tokens->tail = new;
		// ft_printf("minishell: debug -- token added (%s::%d)\n", new->content, new->type);
	}
	else
	{
		tokens->head = new;
		tokens->tail = new;
		// ft_printf("minishell: debug -- token added (%s::%d)\n", tokens->head->content, tokens->head->type);
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
	if (first->next != second && second->prev != first)
		return ;
	first->content = gc_strjoin(first->content, second->content);
	first->type = TOK_WORD;
	tok_delete(second);
}

// void	tok_expand(t_token *token)
// {
// 	t_tokens	*tokens;
// 	t_tokens	*expansion;
// 	char		*value;

// 	tokens = &data()->tokens;
// 	expansion = &data()->expansion;
// 	(void)tokens;
// 	(void)expansion;
// 	if (token->next)
// 		value = exp_get_env_variable(token->next->content);
// 	if ()
	
// 	// at input token, prev->next = expansion->head, next->prev = expansion->tail
// }

void	tok_debug_display(t_tokens *tokens)
{
	t_token	*token;
	const char *debug_type[18] = {"TOK_WORD", "TOK_WHITESPACE", "TOK_PIPE", "TOK_LEFT_PARENTHESIS",
	"TOK_RIGHT_PARENTHESIS", "TOK_LESS", "TOK_DOUBLE_LESS", "TOK_GREATER", "TOK_DOUBLE_GREATER",
	"TOK_QUOTE", "TOK_DOUBLE_QUOTE", "TOK_AND", "TOK_OR", "TOK_VARIABLE", "TOK_WILDCARD",
	"TOK_AMPERSAND", "TOK_SEMICOLON", "TOK_BACKSLASH"};

	token = tokens->head;
	ft_printf("minishell: debug -- display tokens\n");
	while (token)
	{
		ft_printf("[%s::%s]\n", token->content, debug_type[token->type]);
		token = token->next;
	}
}

void	tok_reset(t_tokens *tokens)
{
	tokens->head = NULL;
	tokens->tail = NULL;
	tokens->size = 0;
}

int		tok_is_meta_chararacter(char c)
{
	const	char	meta[13] = {'|', '&', ';', '(', ')', 
								'<', '>', '\"', '\'', '\\', 
								'*', '$', '\0'};
	int 			index;

	index = 0;
	while (meta[index] && meta[index] != c)
		index++;
	if (index < 12)
		return (1);
	return (0);
}

int		tok_make_meta_token(char *position)
{
	static const t_token_key match[16] = {{">>", TOK_DOUBLE_GREATER},
		{"<<", TOK_DOUBLE_LESS}, {"&&", TOK_AND}, {"||", TOK_OR}, 
		{"<", TOK_LESS}, {">", TOK_GREATER}, {"&", TOK_AMPERSAND}, 
		{";", TOK_SEMICOLON}, {"(", TOK_LEFT_PARENTHESIS}, 
		{")", TOK_RIGHT_PARENTHESIS}, {"*", TOK_WILDCARD}, {"$", TOK_VARIABLE}, 
		{"|", TOK_PIPE}, {"\"", TOK_DOUBLE_QUOTE}, {"\'", TOK_QUOTE}, 
		{"\\", TOK_BACKSLASH}
	};
	int		index;
	size_t	length;

	index = 0;
	length = 0;
	while (index < 16 && ft_strncmp(match[index].key, position, ft_strlen(match[index].key)))
		index++;
	if (index < 16)
	{
		length = ft_strlen(match[index].key);
		tok_add(gc_substr(position, 0, length), match[index].type);
		return (length);
	}
	tok_add(gc_substr(position, 0, 1), TOK_WORD);
	return (1);
}

int		tok_make_word_token(char *position)
{
	int	length;

	length = 0;
	while (position[length] && !(tok_is_meta_chararacter(position[length])
		|| ft_isspace(position[length])))
		length++;
	tok_add(gc_substr(position, 0, length), TOK_WORD);
	return (length);
}

int		tok_make_space_token(char *position)
{
	int	length;

	length = 0;
	while (position[length] && ft_isspace(position[length]))
		length++;
	tok_add(gc_substr(position, 0, length), TOK_WHITESPACE);
	return (length);
}

/*	Expansion (with quotes accounted for) must occur before joining quoted string contents, 
	otherwise we complicate the logic of joining tokens
*/
void	expand(t_tokens *tokens)
{
	t_token_type	quoted;
	int				parenthesied;
	t_token	*token;

	quoted = 0;
	parenthesied = 0;
	(void)parenthesied;
	token = tokens->head;
	while (token)
	{
		if ((token->type == TOK_DOUBLE_QUOTE || token->type == TOK_QUOTE) && (!quoted || quoted == token->type))
		{
			if (!quoted)
				quoted = token->type;
			else if (quoted == token->type)
				quoted = 0;
		}
		else if (token->type == TOK_VARIABLE && quoted != TOK_QUOTE)
		{
			if (token->next && token->next->type == TOK_WORD)
			{
				tok_join(token, token->next);
				token->content = gc_strdup("EXPANDED VARIABLE HERE");
			}
			else
			{
				tok_join(token, token->next);
				token->type = TOK_WORD;
			}
		}
		token = token->next;
	}
	if (quoted)
		ft_fprintf(2, "minishell: syntax error (unclosed quote)\n");
	ft_printf("minishell: debug -- variables expanded\n");
}

void	quote(t_tokens *tokens)
{
	t_token_type	quoted;
	int				parenthesied;
	t_token			*token;

	quoted = 0;
	parenthesied = 0;
	(void)parenthesied;
	token = tokens->head;
	while (token)
	{
		if ((token->type == TOK_DOUBLE_QUOTE || token->type == TOK_QUOTE) && (!quoted || quoted == token->type))
		{
			if (!quoted)
				quoted = token->type;
			else if (quoted == token->type)
				quoted = 0;
			tok_delete(token);
			token = token->next;
			continue ;
		}
		else if (quoted && token->next && token->next->type != quoted)
		{
			tok_join(token, token->next);
			continue ;
		}
		else if (!quoted && token->type == TOK_WHITESPACE)
			tok_delete(token);
		token = token->next;
	}
	ft_printf("minishell: debug -- quote contents joined\n");
}

void	tokenize(char *line)
{
	size_t	index;

	if (line[0] == '\0')
		return ;
	index = 0;
	gc_mode(GC_LEXING);
	while (line[index])
	{
		if (tok_is_meta_chararacter(line[index]))
			index += tok_make_meta_token(&line[index]);
		else if (ft_isspace(line[index]))
			index += tok_make_space_token(&line[index]);
		else
			index += tok_make_word_token(&line[index]);
	}
	expand(&data()->tokens);
	quote(&data()->tokens);
	tok_debug_display(&data()->tokens);
	tok_reset(&data()->tokens);
}

/*
cat test.txt | grep $A && printf "contains" || printf "does not contain"; printf "mentions of '$A'\n"
*/