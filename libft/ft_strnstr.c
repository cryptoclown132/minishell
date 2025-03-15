/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:09:55 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/28 19:21:26 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;

	i = 0;
	if (ft_strlen(needle) == ft_strlen(""))
		return ((char *)haystack);
	while (i < ft_strlen(haystack))
	{
		if (i == len)
			return (NULL);
		if (ft_strncmp(&haystack[i], needle, ft_strlen(needle)) == 0)
		{
			if (i + ft_strlen(needle) - 1 >= len)
				return (NULL);
			else
				return ((char *)(&haystack[i]));
		}
		i++;
	}
	return (NULL);
}
