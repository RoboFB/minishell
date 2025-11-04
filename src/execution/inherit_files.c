/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inherit_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:36:02 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 15:26:05 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inherit_files(t_expression *cmd)
{
	t_file	*head;

	if (cmd == NULL || cmd->first == NULL || cmd->second == NULL)
		return ;
	head = file_pop_back(&cmd->files);
	while (head)
	{
		if (head->type == NOT_SET)
			save_close(&head->fd);
		else if (head->type == PATH_STDIN_READ || head->type == FD_HEREDOC_READ
			|| head->type == FD_PIPE_READ)
			file_append_front(&cmd->first->files, head);
		else
		{
			if (cmd->type != OPERATOR_PIPE)
				file_append_front(&cmd->first->files, file_dup_values(head));
			file_append_front(&cmd->second->files, head);
		}
		head = file_pop_back(&cmd->files);
	}
	return ;
}

void	pipe_add_front(t_expression *cmd)
{
	file_add_front(&cmd->first->files);
	cmd->first->files->type = FD_PIPE_WRITE;
	file_add_front(&cmd->second->files);
	cmd->second->files->type = FD_PIPE_READ;
	save_pipe(&cmd->first->files->fd, &cmd->second->files->fd);
	return ;
}
