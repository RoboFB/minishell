/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/08 17:23:58 by rgohrig          ###   ########.fr       */
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
	while (true)
	{
		gc_clear_temporary();
		gc_mode(GC_TEMPORARY);
		line = gc_readline(STYLE BG_WHITE AND BOLD START " minishell " END " % ");
		if (line == NULL || *line == '\0')
			continue;
		add_history(line);
		parse(line, &data()->tokens);
		run_tree(data()->tree_root);
	}
	exit_shell(EXIT_GENERAL_ERROR);
	return (EXIT_FAILURE);
}
