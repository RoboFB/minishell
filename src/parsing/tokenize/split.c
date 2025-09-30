/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:32:04 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/28 22:34:32 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_line(char *line, t_tokens *list)
{
	size_t		index;

	index = 0;
	while (line && line[index])
	{
		if (is_meta_chararacter(line[index]))
			index += tok_make_meta_token(&line[index], list);
		else if (ft_isspace(line[index]))
			index += tok_make_space_token(&line[index], list);
		else
			index += tok_make_word_token(&line[index], list);
	}
}
