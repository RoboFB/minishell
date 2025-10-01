/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/01 14:48:47 by rgohrig          ###   ########.fr       */
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
	gc_mode(GC_PERSISTENT);
	env_init(envp);
	while (1)
	{
		line = readline(STYLE BG_WHITE AND BOLD START " minishell " END " % ");
		tokenize(line);
		if (line && line[0] != '\0')
			add_history(line);
		run_all();
		gc_clear_temporary();
		free(line);
	}
	gc_clear_all();
	return (0);
}
