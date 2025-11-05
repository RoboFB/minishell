/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 18:25:59 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// changes gc modes
void	env_add_line(char *line)
{
	char	***environment_ptr;
	char	**line_ptr;
	int		lines_count;

	gc_mode(GC_PERSISTENT);
	line_ptr = env_get_line_ptr(line);
	if (line_ptr == NULL || *line_ptr == NULL)
	{
		environment_ptr = env_get_ptr();
		lines_count = env_get_size(*environment_ptr);
		gc_realloc((void **)environment_ptr,
			lines_count + 1, lines_count + 2, sizeof(char *));
		(*environment_ptr)[lines_count + 1 - 1] = gc_strdup(line);
		(*environment_ptr)[lines_count + 2 - 1] = NULL;
	}
	else
	{
		*line_ptr = gc_clear_one(*line_ptr);
		*line_ptr = gc_strdup(line);
	}
	gc_mode(GC_TEMPORARY);
	return ;
}

// changes gc modes
void	env_add_line_data(char *key, char *value)
{
	char	*line;

	gc_mode(GC_TEMPORARY);
	line = gc_strjoin_3(key, "=", value);
	env_add_line(line);
	return ;
}

// changes gc modes
void	env_remove_line(char *line)
{
	char	**environment;
	char	**line_ptr;
	int		idx;

	gc_mode(GC_PERSISTENT);
	environment = *env_get_ptr();
	line_ptr = env_get_line_ptr(line);
	idx = 0;
	if (line_ptr == NULL || environment[0] == NULL)
		return ;
	while (environment[idx] != NULL && environment[idx] != *line_ptr)
		idx++;
	if (environment[idx] == *line_ptr)
	{
		environment[idx] = gc_clear_one(environment[idx]);
		idx++;
	}
	while (environment[idx] != NULL)
	{
		environment[idx - 1] = environment[idx];
		idx++;
	}
	environment[idx - 1] = NULL;
	gc_mode(GC_TEMPORARY);
	return ;
}
