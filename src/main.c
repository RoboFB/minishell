/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/06 14:58:59 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "animation.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

static int	main_loop(void)
{
	char	*line;

	while (true)
	{
		*interrupted() = false;
		gc_clear_temporary();
		gc_mode(GC_TEMPORARY);
		animation_init();
		line = get_shell_line(ANIM_DEFAULT_PROMPT);
		animation_kill();
		if (isatty(STDIN_FILENO))
			ft_printf(ANIM_OVERWRITE_NORMAL, data()->last_exit_code);
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				ft_fprintf(2, "exit\n");
			exit_shell(data()->last_exit_code);
		}
		else if (*line == '\0')
			continue ;
		add_history(line);
		parse(line, &data()->tokens);
		run_tree(data()->tree_root);
	}
	return (exit_shell(EXIT_GENERAL_ERROR), EXIT_GENERAL_ERROR);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	gc_init();
	env_init(envp);
	set_shell_level();
	if (isatty(STDIN_FILENO))
		get_pid();
	sig_init();
	main_loop();
	return (exit_shell(EXIT_GENERAL_ERROR), EXIT_GENERAL_ERROR);
}

char	*get_shell_line(const char *prompt)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		return (gc_readline(prompt));
	line = gc_get_next_line(STDIN_FILENO);
	if (line == NULL)
		exit_shell(data()->last_exit_code);
	return (line);
}

void	set_shell_level(void)
{
	char	*level_str;

	gc_mode(GC_TEMPORARY);
	level_str = env_get_line_data("SHLVL");
	if (level_str == NULL || *level_str == '\0')
	{
		env_add_line("SHLVL=1");
		return ;
	}
	env_add_line_data("SHLVL", gc_itoa(ft_atoi(level_str) + 1));
	return ;
}
