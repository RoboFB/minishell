/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:44:14 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/05 12:10:30 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_next(t_token **token)
{
	t_token	*current;

	if (!token || !*token)
		return (NULL);
	current = *token;
	*token = (*token)->next;
	return (current);
}

t_token	*token_peek(t_token **token)
{
	if (!token)
		return (NULL);
	return (*token);
}
