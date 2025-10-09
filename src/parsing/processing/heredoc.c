/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:41:22 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/09 20:53:14 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tmpfile_name(unsigned int id)
{
	char 		*name;

	gc_mode(GC_WORKING);
	name = gc_strjoin("/tmp/minishell-", gc_itoa(data()->pid));
	name = gc_strjoin(name, "-here-");
	name = gc_strjoin(name, gc_itoa(id));
	gc_mode(GC_TEMPORARY);
	return (name);
}

int		heredoc_expand(int fd, char *bytes)
{
	return (write(fd, bytes, ft_strlen(bytes)));
}

t_file	*heredoc_write(t_expression *atom, t_token **token)
{
	t_file	*file;

	file = NULL;
	if ((*token)->next && (*token)->next->type == TOK_WORD)
	{
		file = file_add_back(&atom->files);
		file->path = tmpfile_name((*token)->next->id);
		file->fd = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (file->fd == -1)
			return (NULL);
		write(file->fd, (*token)->next->content, ft_strlen((*token)->next->content));
		close(file->fd);
		file->fd = open(file->path, O_RDONLY, 0600);
		if (file->fd == -1)
		{
			unlink(file->path);
			return (NULL);
		}
		unlink(file->path);
		file->type = FD_HEREDOC_READ;
		*token = (*token)->next;
		//ft_printf("\n%s %d\n", file->path, file->fd);
	}
	return (file);
}
