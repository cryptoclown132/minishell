/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:33:29 by jkroger           #+#    #+#             */
/*   Updated: 2022/06/12 15:33:29 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_string(char *s)
{
	int	output;

	output = 0;
	if (!s)
	{
		output += write(1, "(null)", 6);
		return (output);
	}
	output += write(1, s, ft_strlen(s));
	return (output);
}

int	ft_decimal(int d)
{
	int		output;
	char	*c;

	output = 0;
	c = ft_itoa(d);
	output += write(1, c, ft_strlen(c));
	free(c);
	return (output);
}

int	ft_unsigned_decimal(unsigned int u)
{
	int		output;
	long	n;

	n = (long)u;
	output = 0;
	if (n < 10)
	{	
		n = n % 10;
		output += write(1, &"0123456789"[n], 1);
	}
	else
	{
		output += ft_unsigned_decimal(n / 10);
		n = n % 10;
		output += write(1, &"0123456789"[n], 1);
	}
	return (output);
}

int	ft_hex(unsigned int x, char format)
{
	int	output;

	output = 0;
	if (x < 16)
	{
		x = x % 16;
		if (format == 'x')
			output += write(1, &"0123456789abcdef"[x], 1);
		else
			output += write(1, &"0123456789ABCDEF"[x], 1);
	}
	else
	{
		output += ft_hex(x / 16, format);
		x = x % 16;
		if (format == 'x')
			output += write(1, &"0123456789abcdef"[x], 1);
		else
			output += write(1, &"0123456789ABCDEF"[x], 1);
	}
	return (output);
}

int	ft_pointer(unsigned long int p)
{
	int	output;
	int	digit;

	output = 0;
	if (p < 16)
	{
		if (output == 0)
			output += write(1, "0x", 2);
		digit = p % 16;
		output += write(1, &"0123456789abcdef"[digit], 1);
	}
	else
	{
		output += ft_pointer(p / 16);
		digit = p % 16;
		output += write(1, &"0123456789abcdef"[digit], 1);
	}
	return (output);
}
