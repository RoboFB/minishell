/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:58:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/07 15:56:49 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "animation.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

static char	*main_animation(void)
{
	char	*line;

	animation_init();
	if (data()->animation_enabled)
		line = get_shell_line(ANIM_DEFAULT_PROMPT);
	else
		line = get_shell_line("minishell % ");
	animation_kill();
	if (isatty(STDIN_FILENO) && data()->animation_enabled)
		ft_printf(ANIM_OVERWRITE_NORMAL, data()->last_exit_code);
	return (line);
}

static int	main_loop(void)
{
	char	*line;

	while (true)
	{
		*interrupted() = false;
		gc_clear_temporary();
		gc_mode(GC_TEMPORARY);
		line = main_animation();
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
	if (argc == 2 && (!ft_strncmp(argv[1], "--animation", 12)
			|| !ft_strncmp(argv[1], "-a", 3)))
		data()->animation_enabled = 1;
	gc_init();
	env_init(envp);
	set_shell_level();
	if (isatty(STDIN_FILENO))
		get_pid();
	sig_init();
	main_loop();
	return (exit_shell(EXIT_GENERAL_ERROR), EXIT_GENERAL_ERROR);
}
