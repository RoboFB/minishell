/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:16 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/24 17:29:46 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void blt_cd(t_expression *cmd)
{
	char *old_dir;
	char *new_dir;

	blt_cd_error_check(cmd);
	old_dir = gc_getcwd();
	new_dir = blt_cd_get_new_dir(cmd);
	save_chdir(new_dir);
	env_add_line_data("PWD", gc_getcwd());
	env_add_line_data("OLDPWD", old_dir);
	gc_clear_all();
	exit (EXIT_SUCCESS);
}

void blt_cd_error_check(t_expression *cmd)
{
	if (blt_has_flag(cmd) && cmd->args[1][1] != '\0')
		msg_exit("cd", "no options allowed", EXIT_FAILURE);
	else if (blt_count_args(cmd) >= 2)
		msg_exit("cd", "too many arguments", EXIT_FAILURE);
	return ;
}

char *blt_cd_get_new_dir(t_expression *cmd)
{
	char *new_dir;

	new_dir = NULL;
	if (blt_has_flag(cmd) && cmd->args[1][1] == '\0')
	{
		new_dir = env_get_line_data("OLDPWD");
		if (new_dir == NULL || *new_dir == '\0')
			msg_exit("cd", "OLDPWD not set", EXIT_FAILURE);
		ft_printf("%s\n", new_dir);
	}
	else if (blt_count_args(cmd) == 0)
	{
		new_dir = env_get_line_data("HOME");
		if (new_dir == NULL || *new_dir == '\0')
			msg_exit("cd", "HOME not set", EXIT_FAILURE);
	}
	else if (blt_count_args(cmd) == 1)
		new_dir = cmd->args[1];
	return (new_dir);
}
