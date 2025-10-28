/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:40:33 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/28 18:48:41 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expression_add_arg(t_expression *atom, t_token *token)
{
	if (token->type == TOK_WHITESPACE && !token->is_quoted)
		return ;
	if (!atom->args)
	{
		atom->args = (char **)gc_calloc(2, sizeof(char *));
		atom->args[0] = gc_strdup(token->content);
		atom->args[1] = NULL;
	}
	else
	{
		gc_realloc((void **)&atom->args, atom->argc + 1, atom->argc + 2, sizeof(char *));
		atom->args[atom->argc] = gc_strdup(token->content);
		atom->args[atom->argc + 1] = NULL;
	}
	atom->argc++;
}

// void	expression_add_file(t_expression *atom, t_token **token)
// {
// 	get_redirect(atom, token);
// 	return ;
// }

void	resolve_files(t_expression *expression)
{
	t_file	*current;

	if (!expression->files)
		return ;
	current = expression->files;
	while (current)
	{
		if (!current->collection.head)
			return ;
		if (current->type == FD_HEREDOC_READ)
		{
			heredoc_write(current);
			current = current->next;
			continue ;
		}
		strip_leftover_vars(&current->collection);
		expand(&current->collection);
		join_quotes(&current->collection);
		strip_whitespace(&current->collection);
		wildcards(&current->collection);
		if (!current->collection.head || current->collection.head->next)
			syntax_error("ambiguous redirect\n", 0);
		else
			current->path = current->collection.head->content;
		current = current->next;
	}
}

void	resolve(t_expression *expression)
{
	t_token	*token;

	strip_leftover_vars(&expression->collection);
	expand(&expression->collection);
	join_quotes(&expression->collection);
	strip_whitespace(&expression->collection);
	wildcards(&expression->collection);
	resolve_files(expression);
	token = expression->collection.head;
	while(token)
	{
		expression_add_arg(expression, token);
		token = token->next;
	}
	if (expression->args)
		expression->name = expression->args[0];
}

void	parse(char *line, t_tokens *list)
{
	tokenize(line, list);
	quote(list);
	strip_quotes(list);
	set_delimiters(list);
	contract(list);
	if (!valid_prompt(list))
		syntax_error("syntax error", NULL);
	if (!*interrupted())
		list_to_tree();
}
