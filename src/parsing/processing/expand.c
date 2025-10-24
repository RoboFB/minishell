/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:42:48 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/24 16:32:08 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tok_expansion(t_token *token, char *line, t_tokens *tokens)
{
	t_tokens	*list;
	t_token		*index;

	if (!line)
	{
		tok_delete(&token, tokens);
		return ;
	}
	list = &data()->expansion;
	line_split(line, list);
	index = list->head;
	while (index)
	{
		if (index->type != TOK_WHITESPACE && index->type != TOK_WILDCARD)
			index->is_quoted = TOK_QUOTE;
		index = index->next;
	}
	if (token->prev)
		token->prev->next = list->head;
	else
		tokens->head = list->head;
	if (list->head)
		list->head->prev = token->prev;
	if (token->next)
		token->next->prev = list->tail;
	if (list->tail)
		list->tail->next = token->next;
	list->head = NULL;
	list->tail = NULL;
}

/*	Expansion (with quotes accounted for) must occur before joining
	quoted string contents, otherwise we complicate the logic of joining tokens
*/
void	expand(t_tokens *tokens)
{
	t_token	*token;
	char	*value;

	token = tokens->head;
	while (token)
	{
		if (token->type == TOK_VARIABLE && token->is_quoted != TOK_QUOTE && token->content[1])
		{
			if (token->content[1] == '$')
				token->content = gc_itoa(data()->pid);
			else if (token->content[1] == '?')
				token->content = gc_itoa(data()->last_exit_code);
			else
			{
				value = env_get_line_data(&token->content[1]);
				if (!value || !value[0])
				{
					tok_delete(&token, tokens);
					continue ;
				}
				else if (token->is_quoted != TOK_DOUBLE_QUOTE)
					tok_expansion(token, value, tokens);
				else
					token->content = value;
			}
			token->type = TOK_WORD;
		}
		if (token)
			token = token->next;
	}
}

void	receive_pid(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	data()->pid = info->si_pid;
	return ;
}

pid_t	get_pid(void)
{
	struct sigaction sa;

	sa.sa_sigaction = &receive_pid;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR2, &sa, NULL) < 0)
		return (-1);
	kill(0, SIGUSR2);
	while (!data()->pid);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR2, &sa, NULL) < 0)
		return (-1);
	return (data()->pid);
}
