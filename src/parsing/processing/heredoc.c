/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:41:22 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/09 21:49:46 by modiepge         ###   ########.fr       */
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

ssize_t		write_until_variable(int fd, char *bytes)
{
	size_t	length;

	length = 0;
	while (bytes && bytes[length] && bytes[length] != '$')
		length++;
	if (length > 0)
		write(fd, bytes, length);
	return (length);
}

ssize_t		write_variable(int fd, char *bytes, t_token_type quoted)
{
	char 	*var;
	size_t	length;

	length = 1;
	if (quoted)
		return (write(fd, "$", 1));
	if (bytes[length] == '$')
		var = gc_itoa(data()->pid);
	else if (bytes[length] == '?')
		var = gc_itoa(data()->last_exit_code);
	else
	{
		while (bytes[length] && (ft_isalnum(bytes[length])
			|| bytes[length] == '_'))
			length++;
		var = env_get_line_data(gc_substr(bytes, 1, length - 1));
	}
	if (var)
		write(fd, var, ft_strlen(var));
	if (bytes[length] == '$' || bytes[length] == '?')
		return (2);
	return (length);
}

int		heredoc_expand(int fd, char *bytes, t_token_type quoted)
{
	ssize_t	read;
	ssize_t	add;

	read = 0;
	while (bytes[read])
	{
		if (bytes[read] == '$')
			add = write_variable(fd, &bytes[read], quoted);
		else
			add = write_until_variable(fd, &bytes[read]);
		if (add < 0)
			return (-1);
		read += add;
	}
	return (1);
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
		heredoc_expand(file->fd, (*token)->next->content,
			(*token)->next->is_quoted);
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
