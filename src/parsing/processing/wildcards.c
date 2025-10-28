/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:56:27 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/27 19:00:06 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wildcards(t_tokens *list)
{
	t_token *current;

	current = list->head;
	while (current)
	{
		if (current->type == TOK_WILDCARD && !current->is_quoted)
			current->content = gc_strdup("WILDCARD");
		current = current->next;
	}
}
