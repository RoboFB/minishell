/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:07:13 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/28 21:18:26 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void heredoc_expand(int fd, char *line)
// {
// 	char *lline;

// 	lline = line;
// 	while (lline[0])
// 	{
// 		write(fd, lline, lline - ft_strchr(lline, '$'));
// 		lline = ft_strchr(lline, '$') + 1;
// 	}
// }

// void heredoc_in(t_atom *atom, t_token *token)
// {
// 	char	*line;
// 	char	*delimiter;
// 	bool	expand;
// 	int		pipeend[2];

// 	if (token->next && token->next->type == TOK_WORD)
// 	{
// 		delimiter = token->next->content;
// 		expand = !(token->next->is_quoted);
// 	}
// 	line = readline("> ");
// 	pipe(pipeend);
// 	while (line)
// 	{
// 		if (line && !ft_strncmp(delimiter, line, ft_strlen(line)))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		// write(pipeend[1], line, ft_strlen(line));
// 		ft_printf("%s\n", line);
// 		close(pipeend[1]);
// 		free(line);
// 	}
// }

t_file	*redirect_out(t_atom *atom, t_token **token)
{
	t_file		*file;

	file = NULL;
	if ((*token)->next && (*token)->next->type == TOK_WORD)
	{
		file = file_add(&atom->files);
		file->path = gc_strdup((*token)->next->content);
		if ((*token)->type == TOK_DOUBLE_GREATER)
			file->type = PATH_STDOUT_WRITE_APPEND;
		if ((*token)->type == TOK_GREATER)
			file->type = PATH_STDOUT_WRITE;
		*token = (*token)->next;
	}
	return (file);
}

t_file	*redirect_in(t_atom *atom, t_token **token)
{
	t_file		*file;

	file = NULL;
	if ((*token)->next && (*token)->next->type == TOK_WORD)
	{
		file = file_add(&atom->files);
		file->path = gc_strdup((*token)->next->content);
		file->type = PATH_STDIN_READ;
		*token = (*token)->next;
	}
	return (file);
}

t_file	*file_last(t_file *files)
{
	while (files)
	{
		if (!files->next)
			break ;
		files = files->next;
	}
	return (files);
}

t_file	*file_add_front(t_file **files)
{
	t_file	*new;

	gc_mode(GC_PARSING);
	new = (t_file *)gc_calloc(1, sizeof(t_file));
	new->next = NULL;
	new->type = -1;
	new->fd = -1;
	if (!*files)
		return (NULL);
	if (!*files)
	{
		new->next = *files;
		*files = new;
		return (new);
	}
	return (new);
}

t_file	*file_add(t_file **files)
{
	t_file	*new;
	t_file	*last;

	gc_mode(GC_PARSING);
	new = (t_file *)gc_calloc(1, sizeof(t_file));
	new->next = NULL;
	new->type = -1;
	new->fd = -1;
	if (!new)
		return (NULL);
	if (!*files)
	{
		*files = new;
		return (new);
	}
	last = file_last(*files);
	last->next = new;
	return (new);
}

t_filetype	get_redirect(t_atom *atom, t_token **token)
{
	t_file	*file;

	file = NULL;
	if ((*token)->type == TOK_LESS)
		file = redirect_in(atom, token);
	else if ((*token)->type == TOK_GREATER || (*token)->type == TOK_DOUBLE_GREATER)
		file = redirect_out(atom, token);
	if (file)
		return (file->type);
	return (-1);
}
