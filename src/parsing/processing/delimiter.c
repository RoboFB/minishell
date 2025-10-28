/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 21:33:34 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/27 18:17:26 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_delimiters(t_tokens *list)
{
	t_token	*token;

	token = list->head;
	while (token)
	{
		if (token && token->next && token->is_quoted == 0
			&& token->type == TOK_DOUBLE_LESS)
			get_delimiter(token->next, list);
		token = token->next;
	}
}

// t_token	*get_pattern(t_token *token, t_tokens *list)
// {
// 	t_token	*first;
// 	t_token	*last;

// 	first = token;
// 	last = token;
// 	while (first
// 		&& ((first->type != TOK_WHITESPACE && first->is_quoted == 0)
// 		|| !token_is_separator(first)
// 		|| !token_is_redirect(first)))
// 	{
// 		first = first->prev;
// 	}
// 	while (last
// 		&& ((last->type != TOK_WHITESPACE && last->is_quoted == 0)
// 		|| !token_is_separator(last)
// 		|| !token_is_redirect(last)))
// 	{
// 		last = last->next;
// 	}
// 	while (first != last)
// 	{
// 		tok_join(first, first->next, list);
// 		if (first)
// 			first = first->next;
// 	}
// }


void	heredoc_in(t_token **token)
{
	char				*line;
	char				*delimiter;
	static unsigned int	id;
	int					pid;
	int status;

	gc_mode(GC_WORKING);
	if (!token || !*token)
		return ;
	delimiter = gc_strdup((*token)->content);
	(*token)->content =  gc_strdup("");
	pid = save_fork();
	if (pid == 0)
	{
		sig_reset();
		while (true)
		{
			line = get_shell_line("> ");
			if (!line
				|| (ft_strlen(line) == ft_strlen(delimiter)
				&& !ft_strncmp(delimiter, line, ft_strlen(line))))
				break ;
			(*token)->content = gc_strjoin((*token)->content, line);
			(*token)->content = gc_strjoin((*token)->content, "\n");
		}
		exit_shell(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		status = 0;
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			data()->last_exit_code = WTERMSIG(status) + EXIT_SIGNAL_BASE;
			(*interrupted()) = true;
		}
	}
	gc_mode(GC_TEMPORARY);
	(*token)->id = ++id;
	(*token)->content = gc_strdup((*token)->content);
}

t_token	*get_delimiter(t_token *token, t_tokens *list)
{
	t_token	*current;
	t_token	*first;
	int		quoted;

	first = tok_skip_whitespace(token);
	quoted = 0;
	if (!first)
		return (NULL);
	current = first->next;
	quoted |= first->is_quoted;
	while (first->next)
	{
		if ((current->type == TOK_WHITESPACE && current->is_quoted == 0)
		|| token_is_separator(current)
		|| token_is_redirect(current))
			break ;
		quoted |= current->is_quoted;
		tok_join(first, current, list);
		if (current)
			current = current->next;
	}
	if (quoted)
		first->is_quoted = TOK_DOUBLE_QUOTE;
	heredoc_in(&first);
	return (token);
}
