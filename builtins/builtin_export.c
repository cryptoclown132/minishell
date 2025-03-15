/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:56:19 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/19 20:35:10 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_var(char **vars, char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	if (!vars)
		return (set_exit_status("Failed to Malloc", 1));
	while (vars[i])
	{
		if (ft_strnstr(vars[i], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (vars[i]);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

void	add_env_loop(t_cmds *cmd, char **envcp, char *var)
{
	int	i;

	i = 0;
	while (envcp && envcp[i])
	{
		if (!ft_strncmp(envcp[i], var, len_equal(var)))
			cmd->env[i] = ft_strdup(var);
		else
			cmd->env[i] = ft_strdup(envcp[i]);
		i++;
	}
	if (!ft_var(envcp, var))
		cmd->env[i++] = ft_strdup(var);
	cmd->env[i] = NULL;
}

void	add_env(t_cmds *cmd, char *var)
{
	int		i;
	char	**envcp;

	if (!var)
		return ;
	envcp = cmd->env;
	if (ft_var(envcp, var))
		cmd->env = malloc((count_env_len(envcp) + 1) * sizeof(char *));
	else
		cmd->env = malloc((count_env_len(envcp) + 2) * sizeof(char *));
	if (!cmd->env)
		return (set_exit_void("Failed to Malloc", 1));
	add_env_loop(cmd, envcp, var);
	if (envcp)
	{
		i = -1;
		while (envcp[++i])
			free(envcp[i]);
		free(envcp);
	}
}

char	**sort_export(char **expo)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (expo[++i])
	{
		j = -1;
		while (expo[++j])
		{
			if (ft_strncmp(expo[j], expo[j + 1], ft_strlen(expo[j])) > 0)
			{
				tmp = expo[j];
				expo[j] = expo[j + 1];
				expo[j + 1] = tmp;
			}
		}
	}
	return (expo);
}

void	builtin_export(t_cmds *cmd)
{
	int	i;
	int	j;

	if (!cmd->cmd_split[1])
		export_without_args(cmd);
	i = 0;
	while (cmd->cmd_split[++i])
	{
		j = export_err(cmd, cmd->cmd_split[i], i);
		if (j == 0 && i == 1)
			return ;
		if (j == 1)
			continue ;
		if (ft_strchr(cmd->cmd_split[i], '='))
			add_env(cmd, cmd->cmd_split[i]);
		else
		{
			if (find_var(cmd->var_lst, cmd->cmd_split[i]))
			{
				add_env(cmd, cmd->cmd_split[i]);
				del_var(cmd, cmd->cmd_split[i]);
			}
		}
	}
}
