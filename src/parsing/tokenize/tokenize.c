/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:55:59 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/28 18:07:51 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_filetype	token_to_filetype(t_token *token)
{
	if (!token)
		return (NOT_SET);
	else if (token->type == TOK_DOUBLE_LESS)
		return (FD_HEREDOC_READ);
	else if (token->type == TOK_DOUBLE_GREATER)
		return (PATH_STDOUT_WRITE_APPEND);
	else if (token->type == TOK_LESS)
		return (PATH_STDIN_READ);
	else if (token->type == TOK_GREATER)
		return (PATH_STDOUT_WRITE);
	else
		return (NOT_SET);
}

void	contract_file(t_token *atom, t_token **token)
{
	t_file	*file;

	if (!token_is_redirect(*token))
		return ;
	file = file_make();
	file->type = token_to_filetype(*token);
	tok_add(*token, &atom->collection);
	(*token)->type = TOK_WHITESPACE;
	*token = (*token)->next;
	*token = tok_skip_whitespace(*token);
	if (token_is_redirect(*token) || token_is_separator(*token))
	{
		syntax_error("syntax error near unexpected token", (*token)->content);
		return ;
	}
	else if (!*token)
			syntax_error("syntax error near EOL, empty redirect", NULL);
	while (*token && !token_is_separator(*token) && !token_is_space(*token))
	{
		tok_add(*token, &file->collection);
		*token = (*token)->next;
	}
	if (file->collection.tail)
		file->collection.tail->next = NULL;
	else
		return ;
	file_append_back(&atom->files, file);
}

t_token	*atomize(t_token **token)
{
	t_token *atom;

	if (!token || !*token)
		return (NULL);
	atom = tok_new("", TOK_ATOM);
	*token = tok_skip_whitespace(*token);
	while (*token && !token_is_separator(*token))
	{
		if (token_is_redirect(*token))
			contract_file(atom, token);
		else
			tok_add(*token, &atom->collection);
		if (*token && !token_is_redirect(*token) && !token_is_separator(*token))
			*token = (*token)->next;
	}
	if (atom->collection.tail)
		atom->collection.tail->next = NULL;
	if (!valid_collection(&atom->collection))
		syntax_error("syntax error", NULL);
	return (atom);
}

void	contract(t_tokens *list)
{
	t_token		*current;
	t_tokens	new;

	current = list->head;
	list_reset(&new);
	while (current)
	{
		if (token_is_separator(current))
		{
			tok_add(current, &new);
			current = current->next;
		}
		else if (token_is_separator(current->prev)
			&& token_is_separator(current->next)
			&& current->type == TOK_WHITESPACE)
			current = current->next;
		else
		{
			tok_add(atomize(&current), &new);
		}
	}
	list->head = new.head;
	list->tail = new.tail;
	list->size = new.size;
}

void	tokenize(char *line, t_tokens *list)
{
	if (line[0] == '\0')
		return ;
	line_split(line, list);
}
