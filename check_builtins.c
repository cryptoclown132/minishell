/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:40:38 by fjerinic          #+#    #+#             */
/*   Updated: 2023/03/20 22:58:48 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_util(t_cmds *cmd_lst)
{
	if (!ft_strncmp(cmd_lst->cmd_split[0], "exit", 5))
	{
		if (cmd_lst->next)
			return (1);
		builtin_exit(cmd_lst);
		return (1);
	}
	return (0);
}

int	unset_util(t_cmds *cmd_lst)
{
	if (!ft_strncmp(cmd_lst->cmd_split[0], "unset", 6))
	{
		if (cmd_lst->next)
			return (1);
		unset(cmd_lst);
		return (1);
	}
	return (0);
}

int	is_builtin(t_cmds *cmd_lst)
{
	get_signals_child();
	if (!check_builtin(cmd_lst->cmd_split[0]) && cmd_lst->err != 0)
	{
		set_err(cmd_lst->err_file, cmd_lst->err);
		return (1);
	}
	if (!ft_strncmp(cmd_lst->cmd_split[0], "cd", 3))
	{
		if (cmd_lst->next)
			return (1);
		cd(cmd_lst);
		return (1);
	}
	else if (!ft_strncmp(cmd_lst->cmd_split[0], "export", 7))
	{
		if (cmd_lst->next)
			return (1);
		builtin_export(cmd_lst);
		return (1);
	}
	else if (unset_util(cmd_lst))
		return (1);
	else if (exit_util(cmd_lst))
		return (1);
	return (0);
}

int	is_builtin2(t_cmds *cmd_lst)
{
	if (!cmd_lst->cmd_split)
		return (0);
	if (!ft_strncmp(cmd_lst->cmd_split[0], "echo", 5))
	{
		echo(cmd_lst);
		return (1);
	}
	else if (!ft_strncmp(cmd_lst->cmd_split[0], "pwd", 4))
	{
		if (cmd_lst->cmd_split[1]
			&& cmd_lst->cmd_split[1][0] == '-')
		{
			set_exit_status("pwd error", 1);
			return (1);
		}
		pwd();
		return (1);
	}
	else if (!ft_strncmp(cmd_lst->cmd_split[0], "env", 4))
	{
		try_env(cmd_lst);
		return (1);
	}
	return (0);
}

void	try_env(t_cmds *cmd_lst)
{
	if (count_env_len(cmd_lst->cmd_split) > 1)
	{
		set_exit_status("Error: env", 1);
		return ;
	}
	env(cmd_lst);
	return ;
}
