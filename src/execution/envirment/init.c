/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 18:22:56 by rgohrig          ###   ########.fr       */
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

char	***env_get_ptr(void)
{
	static char	**environment = NULL;

	return (&environment);
}

// call only once, changes gc modes
void	env_init(char **input_envp)
{
	char	***environment_ptr;
	int		idx;
	int		lines_count;

	gc_mode(GC_PERSISTENT);
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
