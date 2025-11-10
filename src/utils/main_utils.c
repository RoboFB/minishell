/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:56:01 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/07 15:56:45 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_shell_line(const char *prompt)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		return (gc_readline(prompt));
	line = gc_get_next_line(STDIN_FILENO);
	if (line == NULL)
		exit_shell(data()->last_exit_code);
	return (line);
}

void	set_shell_level(void)
{
	char	*level_str;

	gc_mode(GC_TEMPORARY);
	level_str = env_get_line_data("SHLVL");
	if (level_str == NULL || *level_str == '\0')
	{
		env_add_line("SHLVL=1");
		return ;
	}
	env_add_line_data("SHLVL", gc_itoa(ft_atoi(level_str) + 1));
	return ;
}
