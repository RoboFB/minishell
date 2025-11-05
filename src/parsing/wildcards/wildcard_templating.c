/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   templating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:17:53 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/04 19:18:27 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	replaces '*' with a non-printable template character like '\1' as suggested
	by ghodges.

	run after setting quote status to tokens, but before joining tokens
	(e. g. before join_quotes())
*/
void	replace_wildcards(t_tokens *list)
{
	t_token	*current;

	current = list->head;
	while (current)
	{
		if (current->type == TOK_WILDCARD && !current->is_quoted)
			current->content[0] = '\1';
		current = current->next;
	}
}

/*	resets the template character for display

	call this after passing pattern to globbing function
*/
void	reset_wildcards(char *pattern)
{
	while (*pattern)
	{
		if (*pattern == '\1')
			*pattern = '*';
		pattern++;
	}
}
