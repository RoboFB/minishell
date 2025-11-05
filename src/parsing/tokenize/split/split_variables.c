/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:41:51 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/05 14:42:43 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tok_variable(char *position, t_tokens *list)
{
	int	length;

	length = 1;
	while (ft_isalnum(position[length]) || position[length] == '_')
		length++;
	if (length == 1)
	{
		if (position[length] == '$')
		{
			tok_add(tok_new(gc_substr(position, 0, length + 1), TOK_VARIABLE),
				list);
			return (2);
		}
		else if (position[length] == '?')
		{
			tok_add(tok_new(gc_substr(position, 0, length + 1), TOK_VARIABLE),
				list);
			return (2);
		}
		else
			tok_add(tok_new(gc_substr(position, 0, 1), TOK_VARIABLE), list);
	}
	else
		tok_add(tok_new(gc_substr(position, 0, length), TOK_VARIABLE), list);
	return (length);
}

int	tok_home(char *position, t_tokens *list)
{
	if (position[1] == '+' || position [1] == '-')
	{
		tok_add(tok_new(gc_substr(position, 0, 2), TOK_VARIABLE),
			list);
		return (2);
	}	
	else
		tok_add(tok_new(gc_substr(position, 0, 1), TOK_VARIABLE), list);
	return (1);
}
