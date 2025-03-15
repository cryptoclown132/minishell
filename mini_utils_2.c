/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:26:12 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/19 20:31:49 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_both_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (set_exit_status("Failed to Malloc", 1));
	i = 0;
	if (s1)
	{
		i = -1;
		while (s1[++i])
			ptr[i] = s1[i];
		free(s1);
	}
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free(s2);
	return (ptr);
}

int	valid_input(char *input)
{
	int	i;

	i = 0;
	if (!ft_isalpha(input[i]))
		return (0);
	while (input[++i] && input[i] != '=')
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (0);
	}
	return (1);
}

void	free_env(t_cmds *cmd)
{
	int	i;

	i = 0;
	if (cmd->env)
	{
		while (cmd->env[i])
			free(cmd->env[i++]);
		free(cmd->env);
	}
	i = 0;
	if (cmd->var_lst)
	{
		while (cmd->var_lst[i])
			free(cmd->var_lst[i++]);
		free(cmd->var_lst);
	}
	free(cmd);
}

void	fd_closing(int *old_fds, int *new_fds,
			t_cmds *cmd_struct)
{
	if (cmd_struct->prev && cmd_struct->log_op != AND && cmd_struct->log_op != OR)
	{
		close(old_fds[1]);
		close(old_fds[0]);
	}
	if (cmd_struct->next && cmd_struct->log_op != AND && cmd_struct->log_op != OR)
	{
		old_fds[0] = new_fds[0];
		old_fds[1] = new_fds[1];
	}
}

char	*ft_strjoin_zero(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (0);
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
	{
		set_exit_status("Error\n", 1);
		return (NULL);
	}
	while (s1[i] != 0)
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != 0)
	{
		new_str[i++] = s2[j++];
	}
	new_str[i] = 0;
	return (new_str);
}
