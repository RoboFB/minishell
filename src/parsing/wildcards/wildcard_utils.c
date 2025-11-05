/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:19:08 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/04 19:40:21 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*wild_get_next_pattern(char **pattern_pos,
		bool *has_wildcard_before_out)
{
	int		pattern_len;
	char	*pattern;

	*has_wildcard_before_out = false;
	pattern_len = 0;
	while (**pattern_pos == '\1')
	{
		*has_wildcard_before_out = true;
		++(*pattern_pos);
	}
	while ((*pattern_pos)[pattern_len] != '\1'
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
			if (wildcard || wild_is_last_ok(&last_wildcard, name, last_pattern))
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

	if (!*last_wildcard)
		return (false);
	start_of_last = name + ft_strlen(name) - ft_strlen(last_pattern);
	if (ft_strncmp(start_of_last, last_pattern, ft_strlen(last_pattern)) == 0)
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
