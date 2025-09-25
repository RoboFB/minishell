/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:29:05 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/25 14:08:19 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void debung_print_tree(const int level, t_expression *cmd, int depth)
{
	if (!(level == DEBUG_MODE || DEBUG_MODE == -1))
		return ;
	if (cmd->first)
		debung_print_tree(level, cmd->first, depth + 1);
	if (cmd->second)
		debung_print_tree(level, cmd->second, depth + 1);

	// printf("cmd parent: %p\n", cmd->parent);
	// printf("cmd first: %p\n", cmd->first);
	// printf("cmd second: %p\n", cmd->second);
	printf("depth: %d \n", depth);
	printf("cmd name: %s \n", cmd->name);
	// printf("cmd arg 1: %s\n", cmd->args[0]);
	printf("cmd file 1: %p\n", cmd->files);

}