/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/21 00:06:11 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	minishell(t_cmds *cmd_lst)
{
	char	*input;

	get_signals();
	// g_exit_status = 0;
	input = user_input();
	if (!input)
	{
		printf("exit\n");
		g_exit_status = 130;
		free_env(cmd_lst);
		exit(g_exit_status);
	}
	cmd_lst = parse(cmd_lst, &input, cmd_lst->env);

	add_history(input);
	free(input);

	if (cmd_lst->err == -2 || g_exit_status == 130)
	{
		free_cmd_lst(cmd_lst);
		return (0);
	}
	var_lst(cmd_lst);
	


	run_cmds_loop(cmd_lst);
	free_cmd_lst(cmd_lst);
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_cmds	*cmd_lst;

	if (argc > 1)
		return (0);
	(void)argv;
	g_exit_status = 0;
	cmd_lst = cmd_struct(envp, 0);
	while (1)
		minishell(cmd_lst);
}

void	if_first_check(int *old_fds, t_cmds *cmd_struct,
									int previous_command_exists)
{
	if (previous_command_exists)
	{
		if (cmd_struct->infile != 0 && cmd_struct->infile != -1)
		{
			close(old_fds[WRITE_END]);
			dup2(cmd_struct->infile, STDIN_FILENO);
			close(cmd_struct->infile);
			close(old_fds[READ_END]);
		}
		else
		{
			dup2(old_fds[READ_END], STDIN_FILENO);
			close(old_fds[READ_END]);
			close(old_fds[WRITE_END]);
		}
	}
	else
	{
		if (cmd_struct->infile != 0 && cmd_struct->infile != -1)
		{
			dup2(cmd_struct->infile, STDIN_FILENO);
			close(cmd_struct->infile);
		}
	}
}

int	fork_failed(int pid)
{
	if (pid == -1)
	{
		set_exit_status("Error: Could not fork the process", 1);
		return (1);
	}
	return (0);
}

int	run_commands(t_cmds **cmd_lst)
{
	t_run_commands	r;
	int				tmp_log_op;

	r.wait_status = 0;
	r.pid = 0;
	while (*cmd_lst)
	{
		if ((*cmd_lst)->cmd_split && is_builtin((*cmd_lst))) // AND
		{
			if (!pipe_builtin(*cmd_lst, r.old_fds, r.new_fds, 1)
			|| !(*cmd_lst)->next)
			return 0;
			*cmd_lst = (*cmd_lst)->next;
			continue ;
		}
		else if (!pipe_builtin((*cmd_lst), r.old_fds, r.new_fds, 0))
			return 0;
		r.pid = fork();
		if (fork_failed(r.pid))
			return 0;

		execute_redirect(r.pid, r.old_fds, r.new_fds, (*cmd_lst));
		r.err = (*cmd_lst)->err;

		if (*cmd_lst && ((*cmd_lst)->log_op == AND || (*cmd_lst)->log_op == OR))
			break;
		(*cmd_lst) = (*cmd_lst)->next;
	}
	wait_for_children(r.pid, &r.wait_status, r.err);
		
	if (*cmd_lst && ((*cmd_lst)->log_op == AND || (*cmd_lst)->log_op == OR))
	{
		tmp_log_op = (*cmd_lst)->log_op;
		(*cmd_lst) = (*cmd_lst)->next;
		// (*cmd_lst)->prev = 0;
		return tmp_log_op;
	}
	return (0);
}
//echo hi && echo heel || ls  && ls -a || ls -ls && echo dealer
void	run_cmds_loop(t_cmds *cmd_lst) // problem: echo hi && echo heel || ls  && ls -a  // echo hi && echo heel || ls  && ls -a && echo hi
{
	int i; 
	int	tmp_op;

	while (cmd_lst) 
	{
		cmd_lst->prev = 0;
		i = run_commands(&cmd_lst);

		if ((i == AND && g_exit_status != 0) || (i == OR && g_exit_status == 0))
		{
			do
			{
				tmp_op = cmd_lst->log_op;
				
				if (cmd_lst)
					cmd_lst = cmd_lst->next;
				
				if (!cmd_lst || (tmp_op == AND && g_exit_status == 0) 
				|| (tmp_op == OR && g_exit_status != 0)
				|| (cmd_lst->log_op == -1 && tmp_op != i))
					break;
			} while (cmd_lst && (cmd_lst->log_op == i || cmd_lst->log_op == PIPE
				|| cmd_lst->log_op == -1));
			
		}
		g_exit_status = 0;	
	}
}

// printf("logop: %i ++ code ex: %i +++ tmp: %i ++ i: %i\n", cmd_lst->log_op, g_exit_status, tmp_op, i);
// while (cmd_lst && (cmd_lst->log_op == i || cmd_lst->log_op == PIPE || cmd_lst->log_op == -1))
// {
// 	printf("is in while loop:%i\n", cmd_lst->log_op);
// 	cmd_lst = cmd_lst->next;
// }