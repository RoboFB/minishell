/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:11:57 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/04 17:45:11 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	add an argument to args** for the given expression. guards against including
	non-literal whitespace.
*/
void	expression_add_arg(t_expression *atom, t_token *token)
{
	if (token_is_space(token))
		return ;
	if (!atom->args)
	{
		atom->args = (char **)gc_calloc(2, sizeof(char *));
		atom->args[0] = gc_strdup(token->content);
		atom->args[1] = NULL;
	}
	else
	{
		gc_realloc((void **)&atom->args, atom->argc + 1, atom->argc + 2,
			sizeof(char *));
		atom->args[atom->argc] = gc_strdup(token->content);
		atom->args[atom->argc + 1] = NULL;
	}
	atom->argc++;
}

/*	shorthand for the different steps needed to resolve the token-stream
	to produce usable output.

	1.	delete variables with length of 1 (read: single '$' tokens)
		in accordance with bash rules
	2.	expand variables and splice the result into the token-stream,
		or overwrite the content if the variable is in double-quotes
	3.	replace wildcard characters to be able to to be able to distinguish
		them from literals
	4.	join tokens based on whether they are quoted or not
	5.	get rid of any remaining, non-literal whitespace
	6.	match wildcards and splice them into the token stream
*/
void	process(t_tokens *list)
{
	strip_leftover_vars(list);
	expand(list);
	replace_wildcards(list);
	join_quotes(list);
	strip_whitespace(list);
	wildcards(list);
}

/*	guard against none or more than one token remaining after processing
	if there is only one, as intended, set its name as the redirect path
*/
void	set_path(t_file *file)
{
	if (file->collection.head && !file->collection.head->next)
		file->path = file->collection.head->content;
}

void	resolve_files(t_expression *expression)
{
	t_file	*current;

	if (!expression->files)
		return ;
	current = expression->files;
	while (current)
	{
		if (current->type == FD_PIPE_READ || current->type == FD_PIPE_WRITE)
		{
			current = current->next;
			continue ;
		}
		if (!current->collection.head)
			return ;
		if (current->type == FD_HEREDOC_READ)
		{
			heredoc_write(current);
			current = current->next;
			continue ;
		}
		process(&current->collection);
		set_path(current);
		current = current->next;
	}
}

void	resolve(t_expression *expression)
{
	t_token	*token;

	process(&expression->collection);
	resolve_files(expression);
	token = expression->collection.head;
	while (token)
	{
		expression_add_arg(expression, token);
		token = token->next;
	}
	if (expression->args)
		expression->name = expression->args[0];
}
