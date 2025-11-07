/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:40:33 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/07 13:40:31 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *line, t_tokens *list)
{
	tokenize(line, list);
	if (!valid_collection(list))
		return ;
	quote(list);
	strip_quotes(list);
	set_delimiters(list);
	contract(list);
	if (!valid_prompt(list))
		syntax_error("syntax error", NULL);
	if (!*interrupted())
		list_to_tree();
	if (*interrupted())
		data()->tree_root = NULL;
}
