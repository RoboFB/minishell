/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:13 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/17 20:43:05 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void blt_env(t_command *cmd)
{
	int		idx;
	char	**environment;

	if (!(cmd->args == NULL || *cmd->args == NULL || **cmd->args == '\0'))
		msg_exit("env", "too many arguments", EXIT_FAILURE);

	idx = 0;
	environment = *env_get_ptr();
	while (environment[idx] != NULL)
	{
		ft_printf("%s\n", environment[idx]);
		idx++;
	}

	gc_clear_all();
	exit(EXIT_SUCCESS);
}
