/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:27:35 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/28 22:29:47 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// not system call efficient at the moment. Should work though.
void	atom_add_arg(t_atom *atom, t_token *token)
{
	gc_mode(GC_PARSING);
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
	atom->next = token->next;
	token->prev = atom->prev;
	atom->argc++;
	ft_debugf(1, "atomize: added argument\n");
}

void	atom_add_file(t_atom *atom, t_token **token)
{
	gc_mode(GC_PARSING);
	get_redirect(atom, token);
	atom_feed(&atom);
	atom_feed(&atom);
	return ;
}

void	atomize(t_tokens *tokens)
{
	t_token	*token;
	t_atom	*atom;

	token = tokens->head;
	atom = atom_new();
	atom->next = token;
	token->prev = (t_token*)atom;
	token = (t_token*)atom->next;
	while (token)
	{
		ft_debugf(1, "atomize: iteration\n");
		if (token->type == TOK_WORD && !atom->args)
		{
			atom_replace_token(atom, token);
			atom_add_arg(atom, token);
		}
		else if (is_redirect(token))
			atom_add_file(atom, &token);
		else if (token->type == TOK_WORD && atom->args)
			atom_add_arg(atom, token);
		else if (is_operator(token))
			atom = atom_new();
		if (token)
			token = token->next;
	}
}

t_expression	*atom_to_expression(t_atom *atom)
{
	t_expression	*expression;

	if (!atom)
		return (NULL);
	gc_mode(GC_PARSING);
	expression = (t_expression *)gc_calloc(1, sizeof(t_expression));
	expression->type = OPERATOR_CMD;
	expression->args = atom->args;
	expression->files = atom->files;
	expression->name = atom->args[0];
	return (expression);
}
