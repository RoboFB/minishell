/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:56:27 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/06 15:23:00 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wildcards(t_tokens *list)
{
	t_token	*current;

	current = list->head;
	while (current)
	{
		if (current->type == TOK_WILDCARD && !current->is_quoted)
		{
			wildcard_set(current->content, &current->collection);
			reset_wildcards(current->content);
			if (current->collection.head)
			{
				list_splice(current, list, &current->collection);
			}
			else
				current->type = TOK_WORD;
		}
		current = current->next;
	}
}

void	wildcard_set(char *replace_str, t_tokens *list)
{
	char	**input_pp;

	if (replace_str == NULL || *replace_str == '\0')
		return ;
	input_pp = gc_split(replace_str, '/');
	if (replace_str && replace_str[0] == '/')
		wild_add_steps("/", input_pp, list);
	else
		wild_add_steps(".", input_pp, list);
	return ;
}

static bool	wild_add_steps_logic(char *curent_path, char **pattern_pp,
	struct dirent *one_dir, t_tokens *list)
{
	if ((!ft_strncmp(one_dir->d_name, ".", 1)
			&& pattern_pp[0][0] != '.') || !wild_check_name(one_dir->d_name,
			pattern_pp[0]))
		return (false);
	else if (pattern_pp[1] == NULL)
		tok_add(tok_new(gc_strjoin_3(curent_path, "/", one_dir->d_name) + 2,
				TOK_WORD), list);
	else if (one_dir->d_type == DT_DIR)
	{
		wild_add_steps(gc_strjoin_3(curent_path, "/", one_dir->d_name),
			&pattern_pp[1], list);
	}
	return (true);
}

// use "." as start for curent_path
void	wild_add_steps(char *curent_path, char **pattern_pp, t_tokens *list)
{
	DIR				*dir_stream;
	struct dirent	*one_dir;

	if (pattern_pp == NULL || *pattern_pp == NULL)
		return ;
	dir_stream = save_opendir(curent_path);
	if (dir_stream == NULL)
		return ;
	while (true)
	{
		one_dir = readdir(dir_stream);
		if (one_dir == NULL)
			break ;
		else
			if (!wild_add_steps_logic(curent_path, pattern_pp, one_dir, list))
				continue ;
	}
	closedir(dir_stream);
	return ;
}
