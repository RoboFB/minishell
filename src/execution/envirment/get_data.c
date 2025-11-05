/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 18:35:01 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_get_len_key(char *line)
{
	size_t	len_key;

	len_key = 0;
	while (line[len_key] && line[len_key] != '=')
		len_key++;
	return (len_key);
}

int	env_get_size(char **environment)
{
	int	idx;

	idx = 0;
	while (environment != NULL && environment[idx] != NULL)
		idx++;
	return (idx);
}

// R: AA'\0'   BBB=  CCC=bla bla  NULL
char	**env_get_line_ptr(char *line)
{
	char	**environment;
	size_t	len_key;
	int		idx;

	if (line == NULL || *line == '\0')
		return (NULL);
	environment = *env_get_ptr();
	len_key = env_get_len_key(line);
	idx = 0;
	while (environment != NULL && environment[idx] != NULL)
	{
		if (ft_strncmp(environment[idx], line, len_key) == 0
			&& (environment[idx][len_key] == '='
			|| environment[idx][len_key] == '\0'))
			return (environment + idx);
		idx++;
	}
	return (NULL);
}

// R: pointer to start of environment value
// R: (NULL) not found or no =
char	*env_get_line_data(char *line)
{
	char	*value_str;
	char	**line_ptr;

	line_ptr = env_get_line_ptr(line);
	if (line_ptr == NULL)
		return (NULL);
	value_str = *line_ptr + env_get_len_key(line);
	if (*value_str != '=')
		return (NULL);
	value_str++;
	return (value_str);
}
