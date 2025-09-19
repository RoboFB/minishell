/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/15 16:55:39 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* 

env 

string/key is a string of: alpha _ try out    =    str can be almost anything
= and value are optional

AA=ls -la
DD=bla bla bla
BBB=
CCC

*/

int env_get_len_key(char *line)
{
	int	len_key;

	len_key = 0;
	while (line[len_key] && line[len_key] != '=')
		len_key++;
	return (len_key);
}

// R: AA'\0'   BBB=  CCC=bla bla  NULL
char **env_get_line_ptr(char *line)
{
	char **environment;
	int len_key;
	int idx;

	if(line == NULL || *line == '\0')
		return (NULL);
	idx = 0;
	len_key = env_get_len_key(line);
	environment = *env_get_ptr();
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
		value_str = *line_ptr + env_get_len_key(line);
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

int	env_get_size(char **environment)
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
	char		**environment;
	char		**line_ptr;
	int 		lines_count;

	environment = *env_get_ptr();
	line_ptr = env_get_line_ptr(line);
	
	if (line_ptr == NULL || *line_ptr == NULL)
	{
		lines_count = env_get_size(environment);
		*env_get_ptr() = gc_realloc(environment, lines_count + 1, lines_count + 3);
		environment[lines_count + 0] = gc_strdup(line);
		environment[lines_count + 1] = NULL;
	}
	else
	{
		*line_ptr = gc_remove_one(*line_ptr);
		*line_ptr = gc_strdup(line);
	}
	return ;
}

// uses gc_permanent before
void	env_remove_line(char *line)
{
	char		**environment;
	char		**line_ptr;
	int 		lines_count;

	environment = *env_get_ptr();
	line_ptr = env_get_line_ptr(line);
	
	if (line_ptr && *line_ptr)
	{
		lines_count = 0;
		while (environment[lines_count] != NULL && environment[lines_count] != *line_ptr)
			lines_count++;
		if (environment[lines_count] == *line_ptr)
		{
			gc_remove_one(*line_ptr);
			lines_count++;
		}
		while (environment[lines_count] != NULL)
		{
			environment[lines_count - 1] = environment[lines_count];
			lines_count++;
		}
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
		environment_ptr[0][idx] = gc_strdup(input_envp[idx]);
		idx++;
	}
	environment_ptr[0][idx] = NULL;
	return ;
}
