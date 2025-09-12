/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/12 16:00:39 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* 

AA=ls -la
DD=bla bla bla
BBB=
CCC

*/

static int h_get_len_key(char *line)
{
	int	len_key;

	len_key = 0;
	while (line[len_key] && line[len_key] != '=')
		len_key++;
	return (len_key);
}

// R: AA'\0'   BBB=  CCC=bla bla  NULL
static char **env_get_line_ptr(char *line)
{
	char **environment;
	int len_key;
	int idx;

	if(line == NULL || *line == '\0')
		return (NULL);
	idx = 0;
	len_key = h_get_len_key(line);
	environment = *env_get_ptr();
	while (environment != NULL && environment[idx] != NULL)
	{
		if (ft_strncmp(environment[idx], line, len_key) == 0
			&& (environment[idx][len_key+1] == '='
				|| environment[idx][len_key+1] == '\0'))
			return (environment + idx);
		idx++;
	}
	return (NULL);
}

// R: pointer to value or NULL or '\0' if empty
char *env_get_line_data(char *line)
{
	char	**line_ptr;
	char	*value_str;

	line_ptr = env_get_line_ptr(line);

	if (line_ptr == NULL)
		return (NULL);
	else
	{
		value_str = *line_ptr + h_get_len_key(line);
		if (*value_str == '=')
			value_str++;
	}
	return (value_str);
}

char ***env_get_ptr(void)
{
	static char		**environment = NULL;

	return (&environment);
}

static int	env_get_size(char **environment)
{
	int idx;

	idx = 0;
	while (environment != NULL && environment[idx] != NULL)
		idx++;
	return (idx);
}

// uses gc_permanent before
void	env_add_line(char *line)
{
	char		***environment_ptr;
	char		**line_ptr;
	int 		lines_count;

	environment_ptr = env_get_ptr();
	line_ptr = env_get_line_ptr(line);
	
	if (line_ptr == NULL || *line_ptr == NULL)
	{
		lines_count = env_get_size(*environment_ptr);
		*environment_ptr = gc_realloc(lines_count + 2, sizeof(char *)); // gets bigger with zeroed new memory
		(*environment_ptr)[lines_count + 1] = ft_strdup(line);
		(*environment_ptr)[lines_count + 2] = NULL;
	}
	else
	{
		gc_free(*line_ptr);
		*line_ptr = ft_strdup(line);
	}
	return ;
}

// call once, use gc_permanent before
void	env_init(char **input_envp)
{
	char		***environment_ptr;
	int 		idx;
	int 		lines_count;

	lines_count = env_get_size(input_envp);
	environment_ptr = env_get_ptr();
	if (*environment_ptr == NULL)
		*environment_ptr = gc_calloc(lines_count + 1, sizeof(char *));
	idx = 0;
	while (idx < lines_count)
	{
		environment_ptr[0][idx] = ft_strdup(input_envp[idx]);
		idx++;
	}
	environment_ptr[0][idx] = NULL;
	return ;
}
