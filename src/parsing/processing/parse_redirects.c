/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:07:13 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/09 17:59:54 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_file	*heredoc_expand(t_token *token)
// {
// 	char *lline;

// 	lline = line;
// 	while (lline[0])
// 	{
// 		write(fd, lline, lline - ft_strchr(lline, '$'));
// 		lline = ft_strchr(lline, '$') + 1;
// 	}
// }

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
	else if ((*token)->type == TOK_DOUBLE_LESS)
	 	file = heredoc_expand(atom, token);
	if (file)
		return (file->type);
	return (-1);
}
