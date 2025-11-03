/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:54:39 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/31 13:23:38 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool *interrupted(void)
{
	static bool interrupted;

	return (&interrupted);
}

int	syntax_error(char *message, char *near)
{
	if (*interrupted())
		return (-1);
	ft_fprintf(2, "minishell: %s", message);
	if (near)
		ft_fprintf(2, " '%s'", near);
	ft_fprintf(2, "\n");
	*interrupted() = true;
	set_exit_code(EXIT_SYNTAX_ERROR);
	return (-1);
}

bool	valid_collection(t_tokens *list)
{
	t_token	*current;

	current = list->head;
	while (current)
	{
		if (current->type != TOK_WHITESPACE || (current->is_quoted && current->content && current->content[0] != '\0'))
			return (true);
		current = current->next;
	}
	return (false);
}

bool	valid_parenthesis(t_tokens *list)
{
	t_token *current;
	unsigned int	left;
	unsigned int	right;

	current = list->head;
	left = 0;
	right = 0;
	while (current)
	{
		if (current->type == TOK_LEFT_PARENTHESIS)
			left++;
		else if (current->type == TOK_RIGHT_PARENTHESIS)
		{
			if (right > left)
				return (false);
			right++;
		}
		current = current->next;
	}
	if (left == right)
		return (true);
	return (false);
}

bool	valid_order(t_tokens *list)
{
	t_token *current;
	unsigned int	atoms;
	unsigned int	operators;
	bool			last_atom;

	last_atom = false;
	current = list->head;
	atoms = 0;
	operators = 0;
	while (current)
	{
		if (current->type == TOK_ATOM)
		{
			if (last_atom)
			 	return (false);
			atoms++;
			last_atom = true;
		}
		else if (token_is_operator(current) && last_atom)
		{
			if (operators > atoms)
				return (false);
			atoms++;
			last_atom = false;
		}
		current = current->next;
	}
	if (atoms <= operators)
		return (false);
	return (true);
}

bool	valid_prompt(t_tokens *list)
{
	t_token *current;

	current = list->head;
	if (!current || !valid_parenthesis(list) 
		|| token_is_operator(list->tail)
		|| !valid_order(list)
		|| (!token_is_parenthesis(current) && current->type != TOK_ATOM))
		return (false);
	while (current)
	{
		if (token_is_operator(current->prev) && token_is_operator(current))
			return (false);
		current = current->next;
	}
	return (true);
}