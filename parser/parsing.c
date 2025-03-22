/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienkroger <julienkroger@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:48:59 by jkroger           #+#    #+#             */
/*   Updated: 2025/03/22 15:53:28 by julienkroge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_cmd_struct(t_cmds *cmd)
{
	cmd->infile = 0;
	cmd->outfile = 1;
	cmd->err = 0;
	cmd->err_file = NULL;
	cmd->cmd_split = NULL;
	cmd->cmd_path = NULL;
	cmd->next = NULL;

	cmd->log_op = -1;
}

void	free_cmd(t_cmds *cmd, int i)
{
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->cmd_split)
	{
		while (cmd->cmd_split[i])
			free(cmd->cmd_split[i++]);
		free(cmd->cmd_split);
	}
	if (cmd->err_file)
		free(cmd->err_file);
	if (cmd->infile != 0 && cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != 1 && cmd->outfile != -1)
		close(cmd->outfile);
	if (cmd->prev != 0)
		free_env(cmd);
	else
		reset_cmd_struct(cmd);
}

void	free_cmd_lst(t_cmds *cmd_lst)
{
	t_cmds	*tmp_curr;
	t_cmds	*tmp_next;

	tmp_curr = cmd_lst->next;
	while (tmp_curr != NULL)
	{
		tmp_next = tmp_curr->next;
		free_cmd(tmp_curr, 0);
		tmp_curr = tmp_next;
	}
	free_cmd(cmd_lst, 0);
}

void	add_cmd(t_cmds **cmd_lst, t_cmds *cmd)
{
	t_cmds	*first;

	first = *cmd_lst;
	if (*cmd_lst == NULL)
	{
		*cmd_lst = cmd;
		(*cmd_lst)->next = NULL;
	}
	else
	{
		while (first->next != NULL)
			first = first->next;
		first->next = cmd;
		first->next->next = NULL;
	}
}

int	init_cmd_struct(t_tokens **token_lst, t_cmds **cmd_lst, char **envp)
{
	t_init_cmd_struct	i;

	i.prev = 0;
	i.cmd = NULL;
	while (*token_lst != NULL && g_exit_status != 130)
	{
		if (i.prev == 0)
			add_cmd(&(*cmd_lst), init_cmd(*cmd_lst, envp, token_lst, i.prev));
		else
			add_cmd(&(*cmd_lst), init_cmd(i.cmd, envp, token_lst, i.prev));
		if ((*token_lst) != NULL && g_exit_status != 130)
		{
			i.tmp_t = (*token_lst)->next;
			free((*token_lst)->token);
			free(*token_lst);
			*token_lst = i.tmp_t;
		}
		i.prev++;
	}
	if (g_exit_status == 130)
		return (0);
	return (1);
}
