/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:46:31 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/25 17:32:27 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// R: num of converted chars or -1 on error | converts str to number
static int	h_strict_atoi(const char *nptr, int *result)
{
	long int	num;
	int			len;
	int			negative;

	num = 0;
	len = 0;
	negative = 1;
	if (!nptr || !result)
		return (-1);
	if (*nptr == '-')
	{
		negative = -1;
		nptr++;
		len++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = num * 10 + (*nptr - '0') * negative;
		if (num < INT_MIN || num > INT_MAX)
			return (-1);
		nptr++;
		len++;
	}
	*result = (int)num;
	return (len);
}

// R: (0)ok  (-1)Error   | parses one argument
int	blt_one_arg(char const *input, int min, int max, int *out)
{
	if (input == NULL || *input == '\0')
		return (-1);
	if (h_strict_atoi(input, out) != (int)ft_strlen(input))
		return (-1);
	if (*out < min || *out > max)
		return (-1);
	return (0);
}

int blt_count_args(t_expression *cmd)
{
	int count;

	if (cmd->args == NULL || cmd->args[0] == NULL)
		return (0);
	count = 0;
	while (cmd->args[1 + count] != NULL)
		count++;
	return (count);
}

bool blt_has_flag(t_expression *cmd)
{

	if (blt_count_args(cmd) >= 1 && cmd->args[1][0] == '-')
		return (true);
	else
		return (false);
}