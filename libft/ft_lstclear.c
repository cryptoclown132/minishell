/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:57:49 by jkroger           #+#    #+#             */
/*   Updated: 2022/06/02 01:23:06 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*node2;

	if (!lst || !del)
		return ;
	node = *lst;
	while (node != NULL)
	{
		node2 = node->next;
		del(node->content);
		free(node);
		node = node2;
	}
	*lst = NULL;
}
