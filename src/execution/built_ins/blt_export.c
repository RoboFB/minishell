/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:42 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/22 16:41:51 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**h_get_sorted(char **env);
static void	h_print_save(char **save);

void	blt_export(t_expression *cmd)
{
	int	idx;

	if ((cmd->args == NULL || *cmd->args == NULL || **cmd->args == '\0'))
	{
		h_print_save(h_get_sorted(*env_get_ptr()));
	}
	else
	{
		// todo check cmd to be valid and test more
		idx = 0;
		while (cmd->args[idx])
		{
			env_add_line(cmd->args[idx]);
			idx++;
		}
	}
	gc_clear_all();
	exit(EXIT_SUCCESS);
}

static int	h_env_cmp(char *s1, char *s2)
{
	int	n1;
	int	n2;

	n1 = env_get_len_key(s1);
	n2 = env_get_len_key(s2);
	if (n1 < n2)
		return (ft_strncmp(s1, s2, n2));
	else
		return (ft_strncmp(s1, s2, n1));
}

static void	h_print_save(char **save)
{
	int	idx;

	idx = 0;
	while (save[idx] != NULL)
	{
		ft_printf("declare -x %.*s", env_get_len_key(save[idx]), save[idx]);
		if (env_get_line_data(save[idx]) != NULL)
			ft_printf("=\"%s\"", env_get_line_data(save[idx]));
		ft_printf("\n");
		idx++;
	}
}

static char	**h_get_sorted(char **env)
{
	int		in_idx;
	int		out_idx;
	int		count;
	char	**sorted;

	sorted = gc_calloc(env_get_size(env) + 1, sizeof(char *));
	out_idx = 0;
	while (env[out_idx] != NULL)
	{
		count = 0;
		in_idx = 0;
		while (env[in_idx] != NULL)
		{
			if (h_env_cmp(env[out_idx], env[in_idx]) > 0)
				count++;
			in_idx++;
		}
		sorted[count] = env[out_idx];
		out_idx++;
	}
	return (sorted);
}
