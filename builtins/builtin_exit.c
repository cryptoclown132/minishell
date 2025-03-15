/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 11:10:15 by raweber           #+#    #+#             */
/*   Updated: 2023/03/21 00:01:27 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(t_cmds *cmd_struct)
{
	ft_printf("exit\n");
	if (cmd_struct->cmd_split[1] && !check_numeric(cmd_struct->cmd_split[1]))
	{
		ft_putstr_fd("shell: exit: numeric argument required\n", 2);
		g_exit_status = 255;
	}
	else if (cmd_struct->cmd_split[1] && cmd_struct->cmd_split[2])
	{
		ft_putstr_fd("shell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	else if (cmd_struct->cmd_split[1]
		&& check_numeric(cmd_struct->cmd_split[1]))
		g_exit_status = ft_atoi(cmd_struct->cmd_split[1]);
	else
		g_exit_status = 0;
	free_cmd_lst(cmd_struct);
	free_env(cmd_struct);
	exit(g_exit_status);
}
