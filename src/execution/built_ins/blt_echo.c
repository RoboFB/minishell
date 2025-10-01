/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:15 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/30 15:13:36 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	blt_echo(t_expression *cmd)
{
	int		idx;
	bool	newline;

	newline = true;
	idx = 1;
	while (h_is_n_flag(cmd->args[idx]))
	{
		idx++;
		newline = false;
	}
	while (cmd->args && cmd->args[idx])
	{
		ft_printf("%s", cmd->args[idx]);
		if (cmd->args[idx + 1] != NULL)
			ft_printf(" ");
		idx++;
	}
	if (newline)
		ft_printf("\n");
	switch_exit(cmd, EXIT_OK);
	return ;
}

bool	h_is_n_flag(char *str)
{
	int	idx;

	if (str[0] != '-')
		return (false);
	idx = 1;
	while (str[idx] == 'n')
		idx++;
	if (str[idx] == '\0')
		return (true);
	return (false);
}
