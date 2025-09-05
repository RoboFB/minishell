/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:51:08 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/25 18:25:42 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*clear;

	if (!lst || !del)
		return ;
	current = *lst;
	clear = NULL;
	while (current)
	{
		clear = current;
		current = current -> next;
		ft_lstdelone(clear, del);
	}
	*lst = NULL;
}
