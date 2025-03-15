/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:46:54 by jkroger           #+#    #+#             */
/*   Updated: 2022/05/19 19:08:58 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*c;
	char	*d;

	c = (char *)dst;
	d = (char *)src;
	if (src < dst)
	{
		while (len--)
		{
			c[len] = d[len];
		}
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
