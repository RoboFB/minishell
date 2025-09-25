/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:13 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/25 17:15:40 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void blt_env(t_expression *cmd)
{
	int		idx;
	char	**environment;

	if (blt_count_args(cmd) >= 1)
		msg_exit("env", "too many arguments", EXIT_FAILURE);

	idx = 0;
	environment = *env_get_ptr();
	while (environment[idx] != NULL)
	{
		ft_printf("%s\n", environment[idx]);
		idx++;
	}

	switch_exit(cmd, EXIT_SUCCESS);
}
