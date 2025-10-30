/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:56:27 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/30 15:46:42 by modiepge         ###   ########.fr       */
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
			if (current->collection.head)
			{
				if (current->prev)
					current->prev->next = current->collection.head;
				current->collection.head->prev = current->prev;
				if (current->next)
					current->next->prev = current->collection.tail;
				current->collection.tail->next = current->next;
				current = current->collection.head;
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
	char	**out_pp;

	out_pp = NULL;
	if (replace_str == NULL || *replace_str == '\0')
		return ;
	input_pp = gc_split(replace_str, '/');
	wild_add_steps(".", input_pp, list);
	return ;
}

// use "." as start for curent_path
void	wild_add_steps(char *curent_path, char **pattern_pp, t_tokens *list)
{
	DIR				*dir_stream;
	struct dirent	*one_dir;

	if (pattern_pp == NULL || *pattern_pp == NULL)
		return ;
	dir_stream = save_opendir(curent_path);
	while (true)
	{
		one_dir = readdir(dir_stream);
		if (one_dir == NULL)
			break ;
		else if ((!ft_strncmp(one_dir->d_name, ".", 1)
				&& pattern_pp[0][0] != '.') || !wild_check_name(one_dir->d_name,
				pattern_pp[0]))
			continue ;
		else if (pattern_pp[1] == NULL)
			tok_add(tok_new(gc_strjoin_3(curent_path, "/", one_dir->d_name) + 2,
					TOK_WORD), list);
		else if (one_dir->d_type == DT_DIR)
			wild_add_steps(gc_strjoin_3(curent_path, "/", one_dir->d_name),
				&pattern_pp[1], list);
	}
	closedir(dir_stream);
	return ;
}

char	*wild_get_next_pattern(char **pattern_pos,
		bool *has_wildcard_before_out)
{
	int		pattern_len;
	char	*pattern;

	*has_wildcard_before_out = false;
	pattern_len = 0;
	while (**pattern_pos == '*')
	{
		*has_wildcard_before_out = true;
		++(*pattern_pos);
	}
	while ((*pattern_pos)[pattern_len] != '*'
		&& (*pattern_pos)[pattern_len] != '\0')
		pattern_len++;
	pattern = gc_substr(*pattern_pos, 0, pattern_len);
	*pattern_pos += pattern_len;
	return (pattern);
}

bool	wild_check_name(char *name, char *pattern_pos)
{
	char	*pattern;
	char	*last_pattern;
	bool	wildcard;
	bool	last_wildcard;

	if (name == NULL | pattern_pos == NULL)
		return (false);
	wildcard = 0;
	pattern = pattern_pos;
	while (true)
	{
		last_wildcard = wildcard;
		last_pattern = pattern;
		pattern = wild_get_next_pattern(&pattern_pos, &wildcard);
		if (pattern[0] == '\0')
		{
			if (wildcard || wild_is_last_ok(last_wildcard, name, last_pattern))
				return (true);
			break ;
		}
		if (!wild_found_next_match(wildcard, &name, pattern))
			return (false);
		name += ft_strlen(pattern);
	}
	return (*name == '\0');
}

bool	wild_is_last_ok(bool *last_wildcard, char *name, char *last_pattern)
{
	char	*start_of_last;

	if (!last_wildcard)
		return (false);
	start_of_last = name + ft_strlen(name) - ft_strlen(last_pattern);
	if (ft_strncmp(start_of_last, last_pattern, ft_strlen(last_pattern) == 0))
		return (true);
	return (false);
}

bool	wild_found_next_match(bool wildcard, char **name, char *pattern)
{
	if (wildcard)
	{
		*name = ft_strnstr(*name, pattern, ft_strlen(*name));
		if (*name == NULL)
			return (false);
	}
	else
	{
		if (ft_strncmp(*name, pattern, ft_strlen(pattern)) != 0)
			return (false);
	}
	return (true);
}
