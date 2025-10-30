/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:10 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/30 16:40:23 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	blt_pwd(t_expression *cmd)
{
	char	*working_dir;
	char	*pwd_dir;

	if (blt_has_flag(cmd))
	{
		msg_error("pwd", "no options allowed");
		set_exit_code(EXIT_SYNTAX_ERROR);
		return ;
	}
	pwd_dir = env_get_line_data("PWD");
	working_dir = save_getcwd(NULL, 0);
	if (pwd_dir && working_dir
		&& ft_strncmp(pwd_dir, working_dir, ft_strlen(working_dir)) == 0)
	{
		ft_printf("%s\n", pwd_dir);
	}
	else
		ft_printf("%s\n", working_dir);
	free(working_dir);
	set_exit_code(EXIT_OK);
	return ;
}
