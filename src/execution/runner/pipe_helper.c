/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:36:02 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/04 15:59:31 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_add_front(t_expression *cmd)
{
	file_add_front(&cmd->first->files);
	cmd->first->files->type = FD_PIPE_WRITE;
	file_add_front(&cmd->second->files);
	cmd->second->files->type = FD_PIPE_READ;
	save_pipe(&cmd->first->files->fd, &cmd->second->files->fd);
	return ;
}

bool	is_piped_direct(t_expression *cmd)
{
	if (cmd->parent == NULL)
		return (false);
	if (cmd->parent->type == OPERATOR_PIPE)
		return (true);
	else
		return (false);
}