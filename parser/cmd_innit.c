/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_innit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:48:59 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/20 18:28:26 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_tokens *token_lst)
{
	int			i;
	t_tokens	*tmp;

	i = 0;
	tmp = token_lst;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->type == WORD || tmp->type == EQUAL)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	cmd_split_loop(t_tokens **token_lst, t_cmds *cmd, char **envp, int i)
{
	t_tokens	*tmp;

	while (*token_lst != NULL && (*token_lst)->type != PIPE && (*token_lst)->type != AND && (*token_lst)->type != OR)  //AND, OR
	{
		if (cmd->infile != -1 || (*token_lst)->type == DOC
			|| (*token_lst)->type == EQUAL)
		{
			if ((*token_lst)->type == IN || (*token_lst)->type == OUT
				|| (*token_lst)->type == DOC || (*token_lst)->type == APP)
				redir_handler((*token_lst), cmd, envp);
			else if ((*token_lst)->type == WORD || (*token_lst)->type == EQUAL)
				cmd->cmd_split[i++] = (*token_lst)->token;
		}
		tmp = (*token_lst)->next;
		if (((*token_lst)->type != WORD && (*token_lst)->type != EQUAL)
			|| (cmd->err != 0 && (*token_lst)->type != EQUAL))
			free((*token_lst)->token);
		free(*token_lst);
		*token_lst = tmp;
		if (g_exit_status == 130)
			free_token(&(*token_lst));
	}
	if (*token_lst != NULL && (*token_lst)->type == PIPE)
		cmd->log_op = PIPE;
	else if (*token_lst != NULL && (*token_lst)->type == AND)
		cmd->log_op = AND;
	else if (*token_lst != NULL && (*token_lst)->type == OR)
		cmd->log_op = OR;
	return (i);
}

int	cmd_split_redir(t_tokens **token_lst, t_cmds *cmd, char **envp)
{
	int			i;

	i = count_args(*token_lst);
	if (i != 0)
	{
		cmd->cmd_split = malloc((i + 1) * sizeof(char *));
		if (!cmd->cmd_split)
			return (set_exit_int("Failed to Malloc", 1));
	}
	return (cmd_split_loop(token_lst, cmd, envp, 0));
}

char	**new_cmd_split(char **cmd_split, int i, int j)
{
	char	**new_cmd_split;
	int		k;

	new_cmd_split = malloc((i + 1) * sizeof(char *));
	if (!new_cmd_split)
		return (set_exit_status("Failed to Malloc", 1));
	k = -1;
	while (++k < j)
		free(cmd_split[k]);
	k = -1;
	while (++k < i)
	{
		new_cmd_split[k] = ft_strdup(cmd_split[j]);
		free(cmd_split[j++]);
	}
	new_cmd_split[k] = NULL;
	free(cmd_split);
	return (new_cmd_split);
}

t_cmds	*innit_cmd(t_cmds *cmd, char **envp, t_tokens **token_lst, int prev)
{
	int	i;
	int	j;

	j = 0;
	if (prev)
	{
		// if ((**token_lst)->type == AND)
		// 	prev = 0;
		cmd = cmd_struct(envp, prev);
	}
	i = cmd_split_redir(token_lst, cmd, envp);
	if (i == 0)
		no_path_split(cmd);
	else
	{
		cmd->cmd_split[i] = NULL;
		while (cmd->cmd_split[j] && ft_strchr(cmd->cmd_split[j], '=')
			&& valid_input(cmd->cmd_split[j]))
			j++;
		cmd->cmd_path = ft_find_path(envp, cmd->cmd_split[j], cmd);
		if (check_builtin(cmd->cmd_split[j]) && !cmd->cmd_path && cmd->err == 0)
		{
			cmd->err = -3;
			cmd->err_file = ft_strdup(cmd->cmd_split[j]);
		}
		if (cmd->cmd_split[j] && j != 0)
			cmd->cmd_split = new_cmd_split(cmd->cmd_split, i - j, j);
	}
	return (cmd);
}
