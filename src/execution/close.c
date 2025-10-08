/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:51:22 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/03 13:16:04 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


void	save_close(int *fd)
{
	if (fd == NULL || *fd == -1)
		return ;
	if (close(*fd) < 0)
		perror("close failed");// cannot exit here because called maby in exit
	*fd = -1;
	return ;
}

void	close_files(t_file *head)
{
	if (head == NULL)
		return ;
	while (head != NULL)
	{
		ft_debugf(25, "close: fd:%d file_path:%s\n", head->fd, head->path);
		save_close(&head->fd);
		head = head->next;
	}
	return ;
}

void	close_all_files(t_expression *root)
{
	if (root == NULL)
		return ;
	close_files(root->files);
	close_all_files(root->first);
	close_all_files(root->second);
	return ;
}
