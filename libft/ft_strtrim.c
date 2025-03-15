/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:46:37 by jkroger           #+#    #+#             */
/*   Updated: 2022/06/08 14:16:23 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	k;

	k = ft_strlen(set);
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (j < k + 1)
		{
			if (s1[i] == set[j])
				break ;
			else if (set[j] == '\0' && !(s1[i] == set[j]))
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

static int	ft_end(char const *s1, char const *set)
{
	int	l;
	int	j;
	int	k;
	int	i;

	l = ft_strlen(s1);
	k = ft_strlen(set);
	i = ft_start(s1, set);
	while (l > i)
	{
		j = 0;
		while (j < k +1)
		{
			if (set[j] == s1[l] && !(s1[l] == '\0'))
				break ;
			else if (set[j] == '\0' && !(set[j] == s1[l]))
				return (l);
			j++;
		}
		l--;
	}
	return (l);
}

char	*ft_strtrim(char const *s1, char const *set)
{	
	char	*p;
	size_t	i;
	size_t	l;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = ft_start(s1, set);
	l = ft_end(s1, set);
	if (i > l)
		return (NULL);
	p = ft_substr(s1, i, l + 1 - i);
	return (p);
}
