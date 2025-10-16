/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/16 19:41:31 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

int	main(int argc, char **argv, char **envp)
{
	char *line;

	(void)argc;
	(void)argv;

	gc_init();
	// signal_init();
	env_init(envp);
	set_shell_level();
	//get_pid(); // out for tester
	while (true)
	{
		gc_clear_temporary();
		gc_mode(GC_TEMPORARY);
		line = get_shell_line(STYLE BG_WHITE AND BOLD START " minishell " END " % ");
		if (line == NULL || *line == '\0')
			continue;
		add_history(line);
		parse(line, &data()->tokens);
		run_tree(data()->tree_root);
	}
	exit_shell(EXIT_GENERAL_ERROR);
	return (EXIT_FAILURE);
}

char *get_shell_line(const char *prompt)
{
	char *line;

	if (isatty(STDIN_FILENO))
		return (gc_readline(prompt));
	line = gc_get_next_line(STDIN_FILENO);
	if (line == NULL)
		exit_shell(data()->last_exit_code);
	return (line);
}

void set_shell_level(void)
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
