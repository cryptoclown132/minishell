/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:00:03 by jkroger           #+#    #+#             */
/*   Updated: 2022/05/26 18:00:03 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*first;

	first = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (first->next != NULL)
		{
			first = first->next;
		}
		first->next = new;
	}
}
