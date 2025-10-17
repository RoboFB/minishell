/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:40:33 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/17 19:04:40 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expression_add_arg(t_expression *atom, t_token *token)
{
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
		expand(&current->collection);
		join_quotes(&current->collection);
		strip_whitespace(&current->collection);
		wildcards(&current->collection);
		if (current->collection.head->next)
			ft_fprintf(STDERR_FILENO, "minishell: ambiguous redirect\n");
		else
			current->path = current->collection.head->content;
		current = current->next;
	}
}

void	resolve(t_expression *expression)
{
	t_token	*token;

	expand(&expression->collection);
	join_quotes(&expression->collection);
	strip_whitespace(&expression->collection);
	wildcards(&expression->collection);
	resolve_files(expression);
	token = expression->collection.head;
	tok_debug_display(&expression->collection);
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
	// tok_debug_display(list);
	strip_quotes(list);
	set_delimiters(list);
	contract(list);
	list_to_tree();
}
