/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:59:37 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/04 17:35:02 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta_chararacter(char c)
{
	const char	meta[14] = {'|', '&', ';', '(', ')', '<', '>', '\"', '\'',
		'\\', '*', '$', '?', '\0'};
	int			index;

	index = 0;
	while (meta[index] && meta[index] != c)
		index++;
	if (index < 13)
		return (1);
	return (0);
}

void	line_split(char *line, t_tokens *list)
{
	size_t	index;

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
