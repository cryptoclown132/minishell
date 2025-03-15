/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:29:52 by fjerinic          #+#    #+#             */
/*   Updated: 2023/03/21 00:02:52 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_child(int *old_fds, int *new_fds,
			t_cmds *cmd_struct, int previous_command_exists)
{
	if_first_check(old_fds, cmd_struct, previous_command_exists);
	if (cmd_struct->next && cmd_struct->log_op != AND && cmd_struct->log_op != OR) // change here !!
	{
		if (cmd_struct->outfile != 1 && cmd_struct->outfile != -1)
		{
			close(new_fds[READ_END]);
			dup2(cmd_struct->outfile, STDOUT_FILENO);
			close(cmd_struct->outfile);
			close(new_fds[WRITE_END]);
		}
		else
		{
			close(new_fds[READ_END]);
			dup2(new_fds[WRITE_END], STDOUT_FILENO);
			close(new_fds[WRITE_END]);
		}
	}
	else
	{
		if (cmd_struct->outfile != 1 && cmd_struct->outfile != -1)
		{
			dup2(cmd_struct->outfile, STDOUT_FILENO);
			close(cmd_struct->outfile);
		}
	}
}

void	execute_child(int pid, int *old_fds, int *new_fds,
			t_cmds *cmd_lst)
{
	if (pid == 0)
	{
		redirect_child(old_fds, new_fds, cmd_lst,
			cmd_lst->prev);
		if (is_builtin2(cmd_lst) || (!cmd_lst->cmd_path && cmd_lst->err == 0))
			exit(g_exit_status);
		if ((!cmd_lst->cmd_path || access(cmd_lst->cmd_path, X_OK) != 0)
			&& cmd_lst->err != 0)
		{
			set_err(cmd_lst->err_file, cmd_lst->err);
			exit(127);
		}
		else if (cmd_lst->cmd_path)
		{
			execve(cmd_lst->cmd_path,
				cmd_lst->cmd_split, cmd_lst->env);
			set_exit_status("Error: command not found", 127);
		}
	}
}

void	wait_for_children(int pid, int *waitpid_status, int err)
{
	while (pid > 0)
		pid = wait(waitpid_status);
	if (WIFEXITED(*waitpid_status))
		g_exit_status = WEXITSTATUS(*waitpid_status);
	if (err != 0 && err != -3)
		g_exit_status = 1;
	if (err == -3)
		g_exit_status = 127;
}

int	pipe_builtin(t_cmds *cmd_lst, int *old_fds, int *new_fds, int flag)
{
	if (cmd_lst->next || cmd_lst->log_op != AND || cmd_lst->log_op != OR)
	{
		if (pipe(new_fds))
		{
			set_exit_status("Error: Could not create pipe", 1);
			return (0);
		}
		if (flag)
			fd_closing(old_fds, new_fds, cmd_lst);
	}
	return (1);
}

void	execute_redirect(int pid, int *old_fds, int *new_fds,
			t_cmds *cmd_lst)
{
	execute_child(pid, old_fds, new_fds, cmd_lst);
	fd_closing(old_fds, new_fds, cmd_lst);
}
