/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:46:25 by jkroger           #+#    #+#             */
/*   Updated: 2022/06/07 17:03:50 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*c;
	const char	*d;
	size_t		i;

	c = (char *)dst;
	d = (const char *)src;
	if (n == 0 || (!c && !d))
		return (dst);
	i = 0;
	while (i < n)
	{
		c[i] = d[i];
		i++;
	}
	return (dst);
}
