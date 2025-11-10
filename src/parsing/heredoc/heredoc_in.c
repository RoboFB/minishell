/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 21:33:34 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/07 21:09:28 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_collect(t_token *token, char *tmpfile)
{
	char				*line;
	char				*delimiter;

	sig_heredoc();
	signal(SIGTSTP, SIG_IGN);
	delimiter = gc_strdup(token->content);
	data()->heredoc = heredoc_open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	while (data()->heredoc != -1)
	{
		line = get_shell_line("> ");
		if (!line || (ft_strlen(line) == ft_strlen(delimiter)
				&& !ft_strncmp(delimiter, line, ft_strlen(line))))
			break ;
		ft_fprintf(data()->heredoc, "%s\n", line);
	}
	save_close(&data()->heredoc);
	exit_shell(EXIT_SUCCESS);
}

void	heredoc_set(t_token *token, int pid, char *tmpfile)
{
	char				*line;
	int					status;
	int					fd;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		data()->last_exit_code = WTERMSIG(status) + EXIT_SIGNAL_BASE;
		(*interrupted()) = true;
	}
	fd = heredoc_open(tmpfile, O_RDONLY, 0600);
	unlink(tmpfile);
	token->content = gc_strdup("");
	while (fd != -1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		token->content = gc_strjoin(token->content, line);
		free(line);
	}
	save_close(&fd);
}

void	heredoc_in(t_token **token)
{
	static unsigned int	id;
	int					pid;
	char				*tmpfile;

	gc_mode(GC_WORKING);
	if (!token || !*token)
		return ;
	tmpfile = tmpfile_name(id++);
	pid = save_fork();
	if (pid == 0)
		heredoc_collect(*token, tmpfile);
	else if (pid > 0)
		heredoc_set(*token, pid, tmpfile);
	sig_init();
	gc_mode(GC_TEMPORARY);
	(*token)->content = gc_strdup((*token)->content);
	gc_clear(GC_WORKING);
}

t_token	*get_delimiter(t_token *token, t_tokens *list)
{
	t_token	*current;
	t_token	*first;
	int		quoted;

	first = list_skip_whitespace(token);
	quoted = 0;
	if (!first)
		return (NULL);
	current = first->next;
	quoted |= first->is_quoted;
	while (first->next)
	{
		if ((current->type == TOK_WHITESPACE && current->is_quoted == 0)
			|| token_is_separator(current) || token_is_redirect(current))
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
