/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:42 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 15:43:31 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_invalid_key(char *str)
{
	int	idx;
	int	size;

	idx = 0;
	size = env_get_len_key(str);
	if (size == 0 || ft_isdigit(str[idx]))
		return (true);
	while (idx < size)
	{
		if (!((ft_isalnum(str[idx]) || ft_strchr("_", str[idx]))))
			return (true);
		idx++;
	}
	return (idx != size);
}

void	blt_export_to_env_helper(t_expression *cmd, int *exit_code)
{
	int	idx;

	idx = 0;
	while (cmd->args[++idx])
	{
		if (is_invalid_key(cmd->args[idx]))
		{
			ft_fprintf(STDERR_FILENO, "export:%s: not a valid identifier\n",
				cmd->args[idx]);
			*exit_code = EXIT_GENERAL_ERROR;
		}
		else
		{
			env_add_line(cmd->args[idx]);
		}
	}
}
