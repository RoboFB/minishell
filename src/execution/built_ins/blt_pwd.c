/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:10 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/25 17:15:54 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void blt_pwd(t_expression *cmd)
{
	char *working_dir;
	char *pwd_dir;

	if (blt_has_flag(cmd))
	{
		msg_exit("unset", "no options allowed", EXIT_FAILURE);
		switch_exit(cmd, EXIT_FAILURE);
		return ;
	}
	pwd_dir = env_get_line_data("PWD");
	working_dir = save_getcwd(NULL, 0);
	if (ft_strncmp(pwd_dir, working_dir, ft_strlen(working_dir)) == 0)
		ft_printf("%s\n", pwd_dir);
	else
		ft_printf("%s\n", working_dir);
	free(working_dir);
	switch_exit(cmd, EXIT_SUCCESS);
}
