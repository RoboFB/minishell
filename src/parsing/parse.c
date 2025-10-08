/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:40:33 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/07 18:04:49 by modiepge         ###   ########.fr       */
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

void	expression_add_file(t_expression *atom, t_token **token)
{
	get_redirect(atom, token);
	return ;
}

// void	atomize(t_tokens *tokens)
// {
// 	t_token	*token;
// 	t_atom	*atom;

// 	token = tokens->head;
// 	atom = atom_new();
// 	atom->next = token;
// 	token->prev = (t_token*)atom;
// 	token = (t_token*)atom->next;
// 	while (token)
// 	{
// 		ft_debugf(1, "atomize: iteration\n");
// 		if (token->type == TOK_WORD && !atom->args)
// 		{
// 			atom_replace_token(atom, token);
// 			atom_add_arg(atom, token);
// 		}
// 		else if (is_redirect(token))
// 			atom_add_file(atom, &token);
// 		else if (token->type == TOK_WORD && atom->args)
// 			atom_add_arg(atom, token);
// 		else if (is_operator(token))
// 			atom = atom_new();
// 		if (token)
// 			token = token->next;
// 	}
// }

void	resolve(t_expression *expression)
{
	t_token	*token;
	
	expand(&expression->collection);
	strip_quotes(&expression->collection);
	join_quotes(&expression->collection);
	strip_whitespace(&expression->collection);
	token = expression->collection.head;
	while(token)
	{
		if (token_is_redirect(token))
			expression_add_file(expression, &token);
		else
			expression_add_arg(expression, token);
		if (token)
			token = token->next;
	}
	expression->name = expression->args[0];
}

void	parse(char *line, t_tokens *list)
{
	tokenize(line, list);
	quote(list);
	contract(list);
	tok_debug_display(list);
	list_to_tree();
}
