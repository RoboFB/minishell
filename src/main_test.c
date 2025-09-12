/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/12 15:11:10 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	env_init(envp);
	char **env_n = *env_get_ptr();
	int i = 0;
	while (env_n[i] != NULL)
	{
		printf("ENV: %s\n", env_n[i]);
	}
	

	// while (1)
	// {
	// 	ft_putstr_fd("Looping...\n", 1);
	// 	printf("Hello World %s\n", readline("minishell> "));
	// 	/* code */
	// }
	
	return (0);
}
