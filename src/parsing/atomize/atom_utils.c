/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:28:35 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/28 22:28:47 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_atom	*atom_new()
{
	t_atom	*atom;
	gc_mode(GC_LEXING);
	atom = (t_atom *)gc_calloc(1, sizeof(t_atom));
	atom->type = TOK_ATOM;
	ft_debugf(1, "atomize: new atom\n");
	return (atom);
}

void	atom_feed(t_atom **atom)
{
	t_tokens	*tokens;
	t_token		**food;

	if (!(*atom))
		return ;
	tokens = &data()->tokens;
	food = &(*atom)->next;
	if (*food == tokens->tail)
		tokens->tail = (t_token *)atom;
	if ((*food) && (*food)->next)
	{
		(*food)->next->prev = (t_token *)(*atom);
		(*atom)->next = (*food)->next;
	}
	else
		(*atom)->next = NULL;
}

void	atom_replace_token(t_atom *atom, t_token *token)
{
	t_tokens	*tokens;

	tokens = &data()->tokens;
	if (token == tokens->head)
		tokens->head = (t_token *)atom;
	if (token == tokens->tail)
		tokens->tail = (t_token *)atom;
	atom->next = token->next;
	atom->prev = token->prev;
	if (token->next)
		token->next->prev = (t_token *)atom;
	if (token->prev)
		token->prev->next = (t_token *)atom;
	ft_debugf(1, "atomize: atom placed\n");
}

int	atom_count_args(t_atom *atom)
{
	int	count;

	count = 0;
	while (atom->args[count])
		count++;
	return (count);
}
