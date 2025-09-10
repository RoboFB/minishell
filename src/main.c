/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/10 14:41:06 by modiepge         ###   ########.fr       */
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
	(void)argc;
	(void)argv;
	(void)envp;

	while (1)
	{
		
		printf("Hello World %s\n", readline("minishell> "));
		/* code */
	}
	
	return (0);
}
