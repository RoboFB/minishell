/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:56:27 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/17 19:13:55 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wildcards(t_tokens *tokens)
{
	t_token *current;

	current = tokens->head;
	while (current)
	{
		if (current->type == TOK_WILDCARD && !current->is_quoted)
			current->content = gc_strdup("WILDCARD");
		current = current->next;
	}
}