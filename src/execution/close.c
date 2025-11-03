/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:51:22 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/31 17:39:04 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cannot exit here because called maybe in exit
void	save_close(int *fd)
{
	if (fd == NULL || *fd == -1)
		return ;
	if (close(*fd) < 0)
		perror("close failed");
	*fd = -1;
	return ;
}

void	close_files(t_file *head)
{
	if (head == NULL)
		return ;
	while (head != NULL)
	{
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
