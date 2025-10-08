/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:13 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/30 15:12:45 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void blt_env(t_expression *cmd)
{
	int		idx;
	char	**environment;

	if (blt_count_args(cmd) >= 1)
	{
		msg_error("env", "no arguments allowed");
		switch_exit(cmd, EXIT_SYNTAX_ERROR);
		return ;
	}
	idx = 0;
	environment = *env_get_ptr();
	while (environment[idx] != NULL)
		ft_printf("%s\n", environment[idx++]);
	switch_exit(cmd, EXIT_OK);
	return ;
}
