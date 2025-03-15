/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:06:59 by jkroger           #+#    #+#             */
/*   Updated: 2022/06/29 17:49:02 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_convert(const char *str, int i, int c)
{
	long	res;

	res = 0;
	while (str[i])
	{
		if ((str[i] - '0' <= 9 && str[i] - '0' >= 0))
		{
			res = res * 10 + str[i] - '0';
			i++;
		}
		else
			break ;
	}
	return (c * res);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	c;

	c = 1;
	i = 0;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
	i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			c = -1;
		i++;
	}
	return (ft_convert(str, i, c));
}
