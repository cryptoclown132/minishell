/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:32:14 by jkroger           #+#    #+#             */
/*   Updated: 2022/06/29 21:27:00 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_type(const char format, va_list arg)
{
	int		output;
	char	c;

	output = 0;
	if (format == 'c')
	{
		c = va_arg(arg, int);
		output += write(1, &c, 1);
	}
	else if (format == 's')
		output += ft_string(va_arg(arg, char *));
	else if (format == 'd' || format == 'i')
		output += ft_decimal(va_arg(arg, int));
	else if (format == 'u')
		output += ft_unsigned_decimal(va_arg(arg, unsigned int));
	else if (format == 'x' || format == 'X')
		output += ft_hex(va_arg(arg, unsigned int), format);
	else if (format == 'p')
	{
		output += ft_pointer(va_arg(arg, unsigned long int));
	}
	return (output);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		output;
	int		i;

	output = 0;
	va_start(arg, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '%')
				output += write(1, &format[i], 1);
			else
				output += ft_type(format[i], arg);
		}
		else
			output += write(1, &format[i], 1);
		i++;
	}
	va_end(arg);
	return (output);
}
