/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/22 15:19:34 by rgohrig          ###   ########.fr       */
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

// tests robin
/* int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	gc_init();
	gc_mode(GC_PERSISTENT);
	env_init(envp);
	char **env_new = *env_get_ptr();
	int i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(env_new[i], envp[i], ft_strlen(envp[i])) != 0)
			printf("test: env not correct copied:\nnew:%s\nold:%s\n", env_new[i], envp[i]);
		i++;
	}
	printf("PATH: %s\n", *env_get_line_ptr("PATH"));
	env_get_line_ptr("PATHgrerg") == NULL ? printf("OK ") : printf("\nERROR 1\n");
	env_get_line_ptr("wPATH") == NULL ? printf("OK ") : printf("\nERROR 2\n");
	env_get_line_ptr("path") == NULL ? printf("OK ") : printf("\nERROR 3\n");
	env_get_line_ptr("=") == NULL ? printf("OK ") : printf("\nERROR 4\n");
	env_get_line_ptr("") == NULL ? printf("OK ") : printf("\nERROR 5\n");
	env_get_line_ptr("PH") == NULL ? printf("OK ") : printf("\nERROR 6\n");

	// normal key= value
	env_add_line("auto_test= ergerg erge -!@#$%^&*()");
	ft_strncmp(env_get_line_data("auto_test"), " ergerg erge -!@#$%^&*()", 24) == 0
		? printf("OK ") : printf("\nERROR 7\n");

	// overwrite
	env_add_line("auto_test=1");
	env_get_line_data("auto_test") ? printf("OK ") : printf("\nERROR 8\n");

	// no value without =
	env_add_line("auto_test4");
	env_get_line_data("auto_test4") == NULL ? printf("OK ") : printf("\nERROR 9\n");

	// no value with =
	env_add_line("auto_test5=");
	*env_get_line_data("auto_test5") == '\0' ? printf("OK ") : printf("\nERROR 10\n");

	env_get_line_data("no_entry") == NULL ? printf("OK ") : printf("\nERROR 11\n");

	// not defined dont do that
	env_add_line("=2");
	env_add_line("=23523se");


	// remove tests:
	env_add_line("test_rm=test");
	env_remove_line("test_rm=tes");
	env_get_line_ptr("test_rm") == NULL ? printf("OK ") : printf("\nERROR\n");
	env_add_line("test_rm_1");
	env_remove_line("test_rm_1=tes");
	env_get_line_ptr("test_rm_1") == NULL ? printf("OK ") : printf("\nERROR\n");

	// env_remove_line("PATH=wefew rgf");
	// env_get_line_ptr("PATH") == NULL ? printf("OK ") : printf("\nERROR\n");

	printf("\n");

	return 0;
} */


// tests robin
/* int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	gc_init();
	gc_mode(GC_PERSISTENT);
	env_init(envp);


	// env builtin
	// exe_command(&(t_command){0, NULL, NULL, NULL, "env", NULL, NULL, NULL});
	// exe_command(&(t_command){0, NULL, NULL, NULL, "ls", (char *[]){"ls", "-l", NULL}, NULL, NULL});
	// exe_command(&(t_command){0, NULL, NULL, NULL, "ls", (char *[]){"", "-l", NULL}, NULL, NULL});
	
	exe_command(&(t_command){0, NULL, NULL, NULL, "export", (char *[]){"AAABOB=1234567890 123_!@#$%^&*()_+';",NULL}, NULL, NULL});
	// exe_command(&(t_command){0, NULL, NULL, NULL, "export", NULL, NULL, NULL});
	

	return 0;
} */