/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/19 19:15:56 by modiepge         ###   ########.fr       */
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


	gc_init();
	gc_mode(GC_PERSISTENT);
	env_init(envp);
	while (1)
	{
		line = readline(STYLE BG_WHITE AND BOLD START " minishell " END " % ");
		tokenize(line);
		if (line && line[0] != '\0')
			add_history(line);
		gc_clear_temporary();
		free(line);
	}
	gc_clear_all();
	return (0);
}

// // tests robin
// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	gc_init();
// 	gc_mode(GC_PERSISTENT);
// 	env_init(envp);
// 	char **env_new = *env_get_ptr();
// 	int i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		if (ft_strncmp(env_new[i], envp[i], ft_strlen(envp[i])) != 0)
// 			printf("test: env not correct copied:\nnew:%s\nold:%s\n", env_new[i], envp[i]);
// 		i++;
// 	}

// 	// env_add_line("gggg=eeee");
// 	// i = 0;
// 	// while (envp[i] != NULL)
// 	// {
// 	// 	if (ft_strncmp(env_new[i], envp[i], ft_strlen(envp[i])) != 0)
// 	// 		printf("test: env not correct copied:\nnew:%s\nold:%s\n", env_new[i], envp[i]);
// 	// 	i++;
// 	// }

// 	return 0;
// }