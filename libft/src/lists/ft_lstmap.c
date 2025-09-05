/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:27:39 by modiepge          #+#    #+#             */
/*   Updated: 2025/03/27 11:57:46 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*out;
	t_list	*new;
	void	*content;

	out = NULL;
	content = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		content = (*f)(lst -> content);
		new = ft_lstnew(content);
		if (!new)
		{
			del(content);
			ft_lstclear(&out, del);
			return (NULL);
		}
		ft_lstadd_back(&out, new);
		lst = lst -> next;
	}
	return (out);
}
