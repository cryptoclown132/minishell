/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:28:35 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/20 23:09:38 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_error(char *token)
{
	write(2, "shell:  syntax error near unexpected token `", 44);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	g_exit_status = 2;
}

void	set_err(char *token, int err)
{
	write(2, "shell: ", 7);
	write(2, token, ft_strlen(token));
	write(2, ": ", 2);
	if (err == -3)
	{
		g_exit_status = 127;
		write(2, "command not found", 17);
	}
	else
	{
		g_exit_status = 1;
		write(2, strerror(err), ft_strlen(strerror(err)));
	}
	write(2, "\n", 1);
}

void	*set_exit_status(char *str, int err)
{
	g_exit_status = err;
	write(2, "shell: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (NULL);
}

void	set_exit_void(char *str, int err)
{
	g_exit_status = err;
	write(2, "shell: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

int	set_exit_int(char *str, int err)
{
	g_exit_status = err;
	write(2, "shell: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (0);
}
