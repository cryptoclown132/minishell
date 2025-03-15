/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:56:02 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/20 20:38:56 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void disable_echo() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void enable_echo() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	ctrl_c(int status)
{
	if (status == SIGINT)
	{
		g_exit_status = 130;
		disable_echo();
		if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			strerror(errno);
		enable_echo();
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ctrl_c_child(int status)
{
	if (status == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
	}
	if (status == SIGQUIT)
	{
		g_exit_status = 128 + status;
		ft_putstr_fd("Quit\n", 1);
	}
}

void	get_signals(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	get_signals_child(void)
{
	signal(SIGINT, &ctrl_c_child);
	signal(SIGQUIT, &ctrl_c_child);
}
