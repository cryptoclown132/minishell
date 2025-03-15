/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:37:37 by jkroger           #+#    #+#             */
/*   Updated: 2022/06/12 15:37:37 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

int	ft_string(char *s);
int	ft_decimal(int d);
int	ft_unsigned_decimal(unsigned int u);
int	ft_hex(unsigned	int x, char format);
int	ft_pointer(unsigned long int p);
int	ft_printf(const char *format, ...);

#endif