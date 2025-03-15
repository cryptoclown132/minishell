/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:08:36 by jkroger           #+#    #+#             */
/*   Updated: 2022/06/06 15:59:08 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	e;

	d = (unsigned char *)s;
	e = c;
	i = 0;
	while (i < n)
	{
		if (d[i] == e)
			return ((unsigned char *)(&d[i]));
		i++;
	}
	return (NULL);
}
