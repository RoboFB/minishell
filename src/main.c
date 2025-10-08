/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/08 16:44:45 by modiepge         ###   ########.fr       */
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
	env_init(envp);
	while (true)
	{
		gc_mode(GC_EXECUTION);
		line = readline(STYLE BG_WHITE AND BOLD START " minishell " END " % ");
		if (line == NULL || *line == '\0')
		{
			gc_clear_temporary();
			continue;
		}
		add_history(line);
		tokenize(line, &data()->tokens);
		run_all();
		gc_clear_temporary();
	}
	exit_shell(EXIT_OK);
	return (EXIT_FAILURE);
}
