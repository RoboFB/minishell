/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:41:22 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/09 18:34:47 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tmpfile_name(void)
{
	char 		*name;
	static int	index;

	gc_mode(GC_WORKING);
	name = gc_strjoin("/tmp/minishell_", gc_itoa(data()->pid));
	name = gc_strjoin(name, "/");
	name = gc_strjoin(name, gc_itoa(++index));
	name = gc_strjoin(name, "_heredoc");
	gc_mode(GC_TEMPORARY);
	return (name);
}

t_file	*heredoc_expand(t_expression *atom, t_token **token)
{
	t_file	*file;
	char	*name;

	file = NULL;
	if ((*token)->next && (*token)->next->type == TOK_WORD)
	{
		name = tmpfile_name();
		file = file_add_back(&atom->files);
		file->fd = open(name, O_WRONLY | O_CREAT | O_TRUNC);
		if (file->fd != -1)
			return (NULL);
		write(file->fd, (*token)->next->content, ft_strlen((*token)->next->content));
		file->type = FD_HEREDOC_READ;
		*token = (*token)->next;
	}
	return (file);
}
