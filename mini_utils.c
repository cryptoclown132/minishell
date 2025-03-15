/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:59 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/20 17:53:47 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*user_input(void)
{
	char	*prompt;
	char	*input;

	prompt = "shell$> ";
	input = readline(prompt);

	// if (ft_strlen(input))
	// 	add_history(input);//later in code
	return (input);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*c;
	unsigned char	*d;

	if (!s1 || !s2)
		return (1);
	c = (unsigned char *)s1;
	d = (unsigned char *)s2;
	i = 0;
	while (s1[i] || s2[i])
	{
		if (c[i] == d[i])
			i++;
		else
			return (c[i] - d[i]);
	}
	return (0);
}

int	check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	return (1);
}

void	free_token(t_tokens **token)
{
	t_tokens	*tmp;

	while (*token != NULL)
	{
		tmp = (*token)->next;
		free((*token)->token);
		free(*token);
		*token = tmp;
	}
	*token = NULL;
}

t_cmds	*cmd_struct(char **envp, int prev)
{
	t_cmds	*cmd;

	cmd = malloc(sizeof(t_cmds));
	if (!cmd)
		return (set_exit_status("Failed to Malloc", 1));
	cmd->env = copy_env(envp);
	cmd->infile = 0;
	cmd->outfile = 1;
	cmd->err = 0;
	cmd->prev = prev;
	cmd->err_file = NULL;
	cmd->cmd_split = NULL;
	cmd->var_lst = NULL;
	if (prev == 0)
		cmd->next = NULL;


	cmd->log_op = -1;
	return (cmd);
}
