/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:42 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/14 15:57:32 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_invalid_key(char *str);
static char	**h_get_sorted(char **env);
static void	h_print_save(char **save);

void	blt_export(t_expression *cmd)
{
	int	idx;
	int	exit_code;

	exit_code = EXIT_OK;
	gc_mode(GC_TEMPORARY);
	if (blt_count_args(cmd) == 0)
		h_print_save(h_get_sorted(*env_get_ptr()));
	else
	{
		idx = 1;
		while (cmd->args[idx])
		{
			if (is_invalid_key(cmd->args[idx]))
			{
				ft_fprintf(STDERR_FILENO, "export: %s: not a valid identifier\n", cmd->args[idx]);
				exit_code = EXIT_GENERAL_ERROR;
			}
			else
				env_add_line(cmd->args[idx]);
			idx++;
		}
	}
	set_exit_code(exit_code);
	return ;
}

static bool is_invalid_key(char *str)
{
	int idx;
	int size;

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
