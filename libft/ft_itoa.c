/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:10:51 by jkroger           #+#    #+#             */
/*   Updated: 2022/06/06 15:57:53 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		i++;
		return (i);
	}
	else
	{
		if (n < 0)
		{
			i++;
			n = -n;
		}
		while (n > 0)
		{
			n = n / 10;
			i++;
		}
		return (i);
	}
}

char	*ft_itoa(int n)
{
	int		i;
	char	*c;
	long	nbr;

	nbr = n;
	i = ft_count(nbr);
	c = malloc((i + 1) * sizeof(char));
	if (!c)
		return (NULL);
	if (nbr < 0)
	{
		c[0] = '-';
		nbr = -nbr;
	}
	c[i--] = '\0';
	if (nbr == 0)
		c[i++] = nbr + '0';
	while (nbr > 0)
	{
		c[i--] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (c);
}
