/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 00:59:06 by fjerinic          #+#    #+#             */
/*   Updated: 2023/03/20 22:09:43 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_char_index(const char *s, int c)
{
	int		n;

	if (!s)
		return (0);
	n = 0;
	while (s[n] != 0 && s[n] != (char)c)
		n++;
	return (n);
}

int	valid_input_helper_unset(char *cur_cmd, int n)
{
	if (!n)
	{
		if (!ft_isalpha(cur_cmd[n]) && !ft_strchr(cur_cmd, '_')
			&& !ft_strchr(cur_cmd, '\"') && !ft_strchr(cur_cmd, '\''))
		{
			set_exit_status("Error: invalid input to minishell unset", 1);
			return (0);
		}
		return (1);
	}
	else
	{
		if (!ft_isalnum(cur_cmd[n]) && !ft_strchr(cur_cmd, '_')
			&& !ft_strchr(cur_cmd, '\"') && !ft_strchr(cur_cmd, '\''))
		{
			set_exit_status("Error: invalid input to minishell unset", 1);
			return (0);
		}
		return (1);
	}
}

int	check_valid_unset_variable(char *cur_cmd)
{
	int	n;
	int	char_index;

	if (cur_cmd[0] == '-')
	{
		set_exit_status("Error", 2);
		return (0);
	}
	if (!valid_input_helper_unset(cur_cmd, 0))
		return (0);
	n = 1;
	char_index = get_char_index(cur_cmd, '=');
	while (cur_cmd[n] && n < char_index)
	{
		if (!valid_input_helper(cur_cmd, n++))
			return (0);
	}
	return (1);
}

void	reorder_array(t_cmds *cmd_struct, int n)
{
	while (cmd_struct->env[n + 1])
	{
		free(cmd_struct->env[n]);
		cmd_struct->env[n] = ft_strdup(
				cmd_struct->env[n + 1]);
		n++;
	}
	free(cmd_struct->env[n]);
	cmd_struct->env[n] = NULL;
}

void	unset(t_cmds *cmd_struct)
{
	int	n;
	int	j;

	j = 1;
	while (cmd_struct->cmd_split[j])
	{
		if (!check_valid_unset_variable(cmd_struct->cmd_split[j]))
			return ;
		n = 0;
		while (cmd_struct->env[n] && ft_strncmp(cmd_struct->env[n],
				cmd_struct->cmd_split[j],
				ft_strlen(cmd_struct->cmd_split[j])))
			n++;
		if (cmd_struct->env[n] && !ft_strncmp(cmd_struct->env[n],
				cmd_struct->cmd_split[j],
				ft_strlen(cmd_struct->cmd_split[j])))
		{
			reorder_array(cmd_struct, n);
		}
		j++;
	}
}
