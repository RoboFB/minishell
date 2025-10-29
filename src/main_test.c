/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/29 19:01:32 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	animation(void)
// {
// 	const char	*frames[20] = {
// 		STYLE BG_CUSTOM "196" AND BOLD START " minishel🚂" END, 
// 		STYLE BG_CUSTOM "197" AND BOLD START " minishe🚂 " END, 
// 		STYLE BG_CUSTOM "198" AND BOLD START " minish🚂l " END, 
// 		STYLE BG_CUSTOM "199" AND BOLD START " minis🚂ll " END, 
// 		STYLE BG_CUSTOM "200" AND BOLD START " mini🚂ell " END, 
// 		STYLE BG_CUSTOM "201" AND BOLD START " min🚂hell " END, 
// 		STYLE BG_CUSTOM "207" AND BOLD START " mi🚂shell " END, 
// 		STYLE BG_CUSTOM "213" AND BOLD START " m🚂ishell " END, 
// 		STYLE BG_CUSTOM "219" AND BOLD START " 🚂nishell " END, 
// 		STYLE BG_CUSTOM "225" AND BOLD START "🚂inishell " END,
// 		STYLE BG_CUSTOM "231" AND BOLD START " minishell " END, 
// 		STYLE BG_CUSTOM "230" AND BOLD START " minishell " END, 
// 		STYLE BG_CUSTOM "229" AND BOLD START " minishell " END, 
// 		STYLE BG_CUSTOM "228" AND BOLD START " minishell " END, 
// 		STYLE BG_CUSTOM "227" AND BOLD START " minishell " END, 
// 		STYLE BG_CUSTOM "226" AND BOLD START " minishell " END, 
// 		STYLE BG_CUSTOM "220" AND BOLD START " minishell " END, 
// 		STYLE BG_CUSTOM "214" AND BOLD START " minishell " END, 
// 		STYLE BG_CUSTOM "208" AND BOLD START " minishell " END, 
// 		STYLE BG_CUSTOM "202" AND BOLD START " minishell " END
// 	};
// 	const t_expression sleep = {OPERATOR_CMD, NULL, NULL, NULL, "sleep", (char *[]){"sleep", ".09", NULL}, 0, NULL, (t_tokens){NULL, NULL, 0}};
// 	static int	t;
// 	int			pid;

// 	if (t >= 20)
// 		t = 0;
// 	ft_printf("\033[s\r%s %% \033[u", frames[t]);
// 	// usleep(60000);
// 	pid = exe_command((t_expression *)&sleep);
// 	wait_and_set_exit_code(pid);
// 	t++;
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*line;
// 	int		pid;
	
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;


// 	gc_init();
// 	gc_mode(GC_PERSISTENT);
// 	env_init(envp);
// 	//pid = save_fork();
// 	pid = 1;
// 	while (1)
// 	{
// 		if (!pid)
// 		{
// 			//animation();
// 		}
// 		else
// 		{
// 			line = readline("\r" STYLE BG_WHITE AND BOLD START " minishell " END " % ");
// 			parse(line, &data()->tokens);
// 			if (line && line[0] != '\0')
// 				add_history(line);
// 			run_all();
// 			gc_clear_temporary();
// 			free(line);
// 		}
// 	}
// 	gc_clear_all();
// 	return (0);
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


// // testing is broken
/* int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	gc_init();
	gc_mode(GC_PERSISTENT);
	env_init(envp);


// 	char *str[] = {"*", "a*b", "*a*b*", "*hallo", "bye*", "***xxx*****", "*****c", NULL};
// 	// for (char *t_str = str[0]; t_str != NULL; t_str++)
// 	for (int i =0; str[i]; i++)
// 	{
// 		printf("\n1: _%s_\n", str[i]);
// 		bool b = 0;
// 		while (1)
// 		{
// 			char *tmp = wild_get_next_pattern(&str[i], &b);
// 			printf("_%s_   _%s_ ?:_%d_\n", str[i], tmp, b);
// 			if (*tmp == '\0')
// 				break;
// 		}
		
// 	}
	printf("0 valied yes: %s\n", wild_check_name("abc", "*") ? "yes" : "false");
	printf("1 valied 1:%d\n", wild_check_name("abc", "*"));
	printf("2 valied 1:%d\n", wild_check_name("abc", "a*"));
	printf("3 valied 1:%d\n", wild_check_name("abc", "*bc"));
	printf("3.5 valied 1:%d\n", wild_check_name("abc", "*abc"));
	printf("4 valied 1:%d\n", wild_check_name("abc", "*b*"));
	printf("5 valied 1:%d\n", wild_check_name("abc", "*a*b*****c*"));
	printf("6 valied 1:%d\n", wild_check_name("abc", "****c"));
	printf("7 valied 1:%d\n", wild_check_name("abc", "a****"));
	printf("8 valied 1:%d\n", wild_check_name("abc", "****"));
	printf("9 valied 1:%d\n", wild_check_name("", "*"));
	printf("10 valied 1:%d\n", wild_check_name("wefwefwefwe", "*"));
	printf("11 valied 1:%d\n\n", wild_check_name("abc", "abc"));
	printf("11 valied 1:%d\n", wild_check_name("aaa", "*a*a"));
	printf("12 valied 1:%d\n\n", wild_check_name("aa", "*a*a"));
	
	printf("20 valied 0:%d\n", wild_check_name("abc", ""));
	printf("20 valied 0:%d\n", wild_check_name("abc", "b"));
	printf("20 valied 0:%d\n", wild_check_name("abc", "a"));
	printf("20 valied 0:%d\n", wild_check_name("abc", "c"));
	printf("21 valied 0:%d\n", wild_check_name("wefwefwefwe", "*x*"));
	printf("22 valied 0:%d\n", wild_check_name("abc", "*g"));
	printf("23 valied 0:%d\n", wild_check_name("abc", "*b"));
	printf("24 valied 0:%d\n", wild_check_name("abc", "b*"));
	printf("25 valied 0:%d\n", wild_check_name("abc", "ac*"));

	bool b = 0;
	char *grr = "*a*a";
	char *tmp = wild_get_next_pattern(&grr, &b);
	printf("_*c_   _%s_   ?:_%d_\n", tmp, b);
	tmp = wild_get_next_pattern(&grr, &b);
	printf("_*c_   _%s_   ?:_%d_\n", tmp, b);
	tmp = wild_get_next_pattern(&grr, &b);
	printf("_*c_   _%s_   ?:_%d_\n", tmp, b);


	// bool b =0;
	// char *grr = "*c";
	// char *tmp = wild_get_next_pattern(&grr, &b);
	// printf("_*c_   _%s_   ?:_%d_\n", tmp, b);
	// 	tmp = wild_get_next_pattern(&grr, &b);
	// 	printf("_*c_   _%s_   ?:_%d_\n", tmp, b);
	// 	tmp = wild_get_next_pattern(&grr, &b);
	// 	printf("_*c_   _%s_   ?:_%d_\n", tmp, b);


	exit_shell(EXIT_OK);
	return 0;
}

 */