/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/12 19:29:57 by rgohrig          ###   ########.fr       */
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
	(void)envp;

	// env_init(envp);
	// char **env_n = *env_get_ptr();
	// int i = 0;
	// while (env_n[i] != NULL)
	// {
	// 	printf("ENV: %s\n", env_n[i++]);
	// }
	gc_init();
	while (1)
	{
		line = readline(STYLE BG_WHITE AND BOLD START " minishell " END " % ");
		tokenize(line);
		if (line && line[0] != '\0')
			add_history(line);
		free(line);
		gc_clear_all();
	}
	

	// while (1)
	// {
	// 	ft_putstr_fd("Looping...\n", 1);
	// 	printf("Hello World %s\n", readline("minishell> "));
	// 	/* code */
	// }
	
	return (0);
}
