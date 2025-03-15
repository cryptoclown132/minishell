/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:09:19 by jkroger           #+#    #+#             */
/*   Updated: 2022/05/22 15:31:44 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = ft_strlen(dst);
	k = ft_strlen(src);
	if (dstsize == 0 || dstsize <= j)
		return (k + dstsize);
	else
	{
		i = 0;
		while (i < dstsize - j - 1 && src[i])
		{
			dst[i + j] = src[i];
			i++;
		}
		dst[i + j] = '\0';
		return (j + k);
	}
}
