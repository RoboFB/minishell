/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/03 13:10:16 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_data	*data(void)
// {
// 	static t_data	data;

// 	return (&data);
// }

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
// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	gc_init();
// 	gc_mode(GC_PERSISTENT);
// 	env_init(envp);


// 	// env builtin
// 	// exe_command(&(t_expression){0, NULL, NULL, NULL, "env", NULL, NULL});
// 	// exe_command(&(t_expression){0, NULL, NULL, NULL, "ls", (char *[]){"ls", "-l", NULL}, NULL});
// 	// exe_command(&(t_expression){0, NULL, NULL, NULL, "ls", (char *[]){"", "-l", NULL}, NULL});
	
// 	// exe_command(&(t_expression){0, NULL, NULL, NULL, "export", (char *[]){"AAABOB=1234567890 123_!@#$%^&*()_+';",NULL}, NULL});
// 	// run_all(&(t_expression){0, NULL, NULL, NULL, "export", NULL, NULL});
// 	t_file file1 = {FD_PIPE_WRITE, NULL, -1, NULL};
// 	t_file file2 = {FD_PIPE_READ, NULL, -1, NULL};

	// t_expression t1 = {OPERATOR_CMD, NULL, NULL, NULL, "ls", (char *[]){"ls", NULL}, NULL};
// 	t_expression t2 = {OPERATOR_CMD, NULL, NULL, NULL, "cat", (char *[]){"cat", NULL}, NULL};
// 	t_expression start = {OPERATOR_PIPE, NULL, &t1, &t2, NULL, NULL, NULL};
// 	t1.parent = &start;
// 	t2.parent = &start;

// 	t1.files = &file1;
// 	t2.files = &file2;

// 	run_all(&start);
	
// 	gc_clear_all();
// 	return 0;
// }





// testing files functions
// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	gc_init();
// 	gc_mode(GC_PERSISTENT);
// 	env_init(envp);

// 	t_file *f1 = file_make();
// 	debug_files(f1);

// 	// file_add_front(&f1);
// 	// debug_files(f1);
	
// 	// file_add_back(&f1);
// 	// debug_files(f1);
	
// 	file_append_front(&f1, file_copy_values(f1));
// 	debug_files(f1);

// 	// t_expression t1 = {0, NULL, NULL, NULL, NULL, (char *[]){NULL, NULL}, f1};
// 	// debug_tree(&t1);
	

// 	exit_shell(EXIT_OK);
// 	return 0;
// }