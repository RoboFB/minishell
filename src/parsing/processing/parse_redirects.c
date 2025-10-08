/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:07:13 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/08 17:04:38 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void heredoc_expand(int fd, char *line)
{
	char *lline;

	lline = line;
	while (lline[0])
	{
		write(fd, lline, lline - ft_strchr(lline, '$'));
		lline = ft_strchr(lline, '$') + 1;
	}
}

void	heredoc_in(t_expression *atom, t_token **token)
{
	char	*line;
	char	*delimiter;
	bool	expand;

	(void)atom;
	if ((*token)->next && (*token)->next->type == TOK_WORD)
	{
		delimiter = (*token)->next->content;
		expand = !((*token)->next->is_quoted);
	}
	line = readline("> ");
	gc_mode(GC_WORKING);
	while (line)
	{
		if (line && !ft_strncmp(delimiter, line, ft_strlen(line)))
		{
			free(line);
			break ;
		}
		gc_strjoin((*token)->next->content, line);
		gc_strjoin((*token)->next->content, "\n");
		free(line);
		line = readline("> ");
	}
	gc_mode(GC_TEMPORARY);
	(*token)->next->content = gc_strdup((*token)->next->content);
	*token = (*token)->next;
}

t_file	*redirect_out(t_expression *atom, t_token **token)
{
	t_file		*file;

	file = NULL;
	if ((*token)->next && (*token)->next->type == TOK_WORD)
	{
		file = file_add_back(&atom->files);
		file->path = gc_strdup((*token)->next->content);
		if ((*token)->type == TOK_DOUBLE_GREATER)
			file->type = PATH_STDOUT_WRITE_APPEND;
		if ((*token)->type == TOK_GREATER)
			file->type = PATH_STDOUT_WRITE;
		*token = (*token)->next;
	}
	return (file);
}

t_file	*redirect_in(t_expression *atom, t_token **token)
{
	t_file		*file;

	file = NULL;
	if ((*token)->next && (*token)->next->type == TOK_WORD)
	{
		file = file_add_back(&atom->files);
		file->path = gc_strdup((*token)->next->content);
		file->type = PATH_STDIN_READ;
		*token = (*token)->next;
	}
	return (file);
}

t_filetype	get_redirect(t_expression *atom, t_token **token)
{
	t_file	*file;

	file = NULL;
	if ((*token)->type == TOK_LESS)
		file = redirect_in(atom, token);
	else if ((*token)->type == TOK_GREATER 
		|| (*token)->type == TOK_DOUBLE_GREATER)
		file = redirect_out(atom, token);
	// else if ((*token)->type == TOK_DOUBLE_LESS)
	// 	file = heredoc_in(atom, token);
	if (file)
		return (file->type);
	return (-1);
}
