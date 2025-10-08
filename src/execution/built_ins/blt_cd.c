/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:16 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/30 15:15:12 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void blt_cd(t_expression *cmd)
{
	char *old_dir;
	char *new_dir;

	if (blt_cd_error_check(cmd) == -1)
	{
		switch_exit(cmd, EXIT_SYNTAX_ERROR);
		return ;
	}
	gc_mode(GC_EXECUTION);
	old_dir = gc_getcwd();
	new_dir = blt_cd_get_new_dir(cmd);
	if (new_dir == NULL)
	{
		switch_exit(cmd, EXIT_GENERAL_ERROR);
		return ;
	}
	if (chdir(new_dir) == -1)
	{
		perror("cd: chdir failed");
		switch_exit(cmd, EXIT_GENERAL_ERROR);
		return ;
	}
	new_dir = gc_getcwd();
	gc_mode(GC_PERSISTENT);
	env_add_line_data("PWD", new_dir);
	env_add_line_data("OLDPWD", old_dir);
	gc_mode(GC_EXECUTION);
	switch_exit(cmd, EXIT_OK);
	return ;
}

int blt_cd_error_check(t_expression *cmd)
{
	if (blt_has_flag(cmd) && cmd->args[1][1] != '\0')
	{
		msg_error("cd", "no options allowed");
		return (-1);
	}
	else if (blt_count_args(cmd) >= 2)
	{
		msg_error("cd", "too many arguments");
		return (-1);
	}
	return (0);
}

char *blt_cd_get_new_dir(t_expression *cmd)
{
	char *new_dir;

	new_dir = NULL;
	if (blt_has_flag(cmd) && cmd->args[1][1] == '\0')
	{
		new_dir = env_get_line_data("OLDPWD");
		if (new_dir == NULL || *new_dir == '\0')
		{
			msg_error("cd", "OLDPWD not set");
			return (NULL);
		}
		ft_printf("%s\n", new_dir);
	}
	else if (blt_count_args(cmd) == 0)
	{
		new_dir = env_get_line_data("HOME");
		if (new_dir == NULL || *new_dir == '\0')
		{
			msg_error("cd", "HOME not set");
			return (NULL);
		}
	}
	else if (blt_count_args(cmd) == 1)
		new_dir = cmd->args[1];
	return (new_dir);
}
