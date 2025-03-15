/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:48:05 by fjerinic          #+#    #+#             */
/*   Updated: 2023/03/19 19:48:08 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_check_args(t_cmds *cmd_struct)
{
	if (!cmd_struct->cmd_split[1])
	{
		ft_printf("\n");
		return (1);
	}
	else if (!ft_strncmp(cmd_struct->cmd_split[1], "-n", 3)
		&& !cmd_struct->cmd_split[2])
		return (1);
	return (0);
}

static void	echo_no_n(t_cmds *cmd_struct)
{
	int	n;

	n = 2;
	while (cmd_struct->cmd_split[n])
	{
		if (n > 2)
			ft_printf(" ");
		ft_printf("%s", cmd_struct->cmd_split[n++]);
	}
}

static void	echo_n(t_cmds *cmd_struct)
{
	int	n;

	n = 1;
	while (cmd_struct->cmd_split[n])
	{
		if (n > 1)
			ft_printf(" ");
		ft_printf("%s", cmd_struct->cmd_split[n++]);
	}
	ft_printf("\n");
}

void	echo(t_cmds *cmd_struct)
{
	if (echo_check_args(cmd_struct))
		return ;
	if (cmd_struct->cmd_split[1]
		&& !ft_strncmp(cmd_struct->cmd_split[1], "-n", 3))
	{
		echo_no_n(cmd_struct);
	}
	else
	{
		echo_n(cmd_struct);
	}
}
