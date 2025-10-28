/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:54:39 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/28 18:14:03 by modiepge         ###   ########.fr       */
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

bool	valid_prompt(t_tokens *list)
{
	t_token *current;

	current = list->head;
	if (!current || !(token_is_parenthesis(current) || current->type == TOK_ATOM))
		return (false);
	while (current)
	{
		if (token_is_separator(current->prev) && token_is_separator(current) 
			&& !(token_is_parenthesis(current->prev) || token_is_parenthesis(current)))
			return (false);
		if (token_is_parenthesis(current->prev) && token_is_parenthesis(current))
			return (false);
		if (!current->next && token_is_operator(current))
			return (false);
		current = current->next;
	}
	return (true);
}