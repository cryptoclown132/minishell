/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:34:39 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/21 00:11:01 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// #define _GNU_SOURCE 


# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <string.h> 
# include <sys/ioctl.h>
# include <readline/history.h>
# include <readline/readline.h>
// # include </opt/homebrew/opt/readline/include/readline/readline.h>
// # include </opt/homebrew/opt/readline/include/readline/history.h>
// # include </opt/homebrew/opt/readline/include/readline/rlstdc.h>

# include <sys/wait.h>
# include <stdbool.h>
#include <termios.h>


# ifdef __linux__
// Linux
#  define PATH_SIZE 4096
# else
// Mac
#  define PATH_SIZE 1024
# endif

# define READ_END 0
# define WRITE_END 1

extern int	g_exit_status;

/***********/
/* structs */
/***********/

/* for tokens */

enum e_TYPE {
	PIPE,
	IN,
	OUT,
	DOC,
	APP,
	WORD,
	EQUAL,
	AND,
	OR
};

typedef struct s_tokens
{
	enum e_TYPE		type;
	char			*token;


	int				parenthesis_num;


	struct s_tokens	*next;
}t_tokens;

/* for cmds */
typedef struct s_cmds
{
	char			**cmd_split;
	char			*cmd_path;
	int				infile;
	int				outfile;
	char			*err_file;
	int				err;
	int				prev;
	char			**env;
	char			**var_lst;
	struct s_cmds	*next;


	int				log_op;
	int				para_num;
}t_cmds;

/* for norm */
typedef struct s_get_var
{
	int		i;
	int		j;
	int		k;
	char	*var_value;
	char	*tmp;
}t_get_var;

typedef struct s_expan
{
	int			i;
	char		*tmp_var;
}t_expan;

typedef struct s_itw_loop
{
	char	*tmp_str;
	char	tmp;
	int		k;
}t_itw_loop;

typedef struct s_here_loop
{
	char	*input;
	char	*limiter;
	char	*tmp;
}t_here_loop;

typedef struct s_innit_cmd_struct
{
	t_tokens	*tmp_t;
	t_cmds		*cmd;
	int			prev;
}t_innit_cmd_struct;

typedef struct s_run_commands
{
	int		pid;
	int		new_fds[2];
	int		old_fds[2];
	int		wait_status;
	int		err;
}t_run_commands;

/*********/
/* lexer */
/*********/

/* lex_utils.c */
int			quote_len(char *s, int *i);
int			space_len(char *s, int *i);
int			word_len(char *s, int *i);

/* lex_err.c */
int			lex_error_check(char *input);

/* lex_err_red.c */
int			check_redir(char *input);

/* lexer.c */
t_tokens	*lexer(t_tokens *token_lst, char *input, char **envp);

/* token_innit.c */
t_tokens	*innit_token(char *input, int *i, int token_type);
// t_tokens	*innit_token_word(char *input, int *i, char **envp);
t_tokens	*init_token_word(char *input, int *i, char **envp, int para_num);
void		add_token(t_tokens **token_lst, t_tokens *token);
t_tokens	*init_redir(char *input, int *i, int type, char **envp, int para_num);

// t_tokens	*innit_redir(char *input, int *i, int type, char **envp);

/* expander.c */
char		*expander(char *token, char **envp);

/* env_var_utils.c */
char		*get_var(char *token, char **envp);
void		var_exist(char *token, char **envp, int *i, char **var_value);

/**********/
/* parser */
/**********/

/* parser.c */
t_cmds		*parse(t_cmds *cmd_lst, char **input, char **envp);

// t_cmds		*parse(t_cmds *cmd_lst, char *input, char **envp);

/* parsing.c */
int			innit_cmd_struct(t_tokens **token_lst,
				t_cmds **cmd_lst, char **envp);
void		free_cmd(t_cmds *cmd, int i);
void		reset_cmd_struct(t_cmds *cmd_lst);
void		free_cmd_lst(t_cmds *cmd_lst);
void		add_cmd(t_cmds **cmd_lst, t_cmds *cmd);

/* cmd_path.c */
char		*ft_find_path(char **env, char *cmd, t_cmds *cmd_lst);
void		no_path_split(t_cmds *cmd);

/* redir_handler.c */
void		redir_handler(t_tokens *token, t_cmds *cmd, char **env);

/* heredoc_utils.c */
void		here_doc_loop(t_tokens *token, int fd, char **env);

/* cmd_innit.c */
t_cmds		*innit_cmd(t_cmds *cmd_lst, char **envp,
				t_tokens **token_lst, int prev);

/* env_list.c */
char		**copy_env(char **envp);
int			count_env_len(char **envp);

/**********/
/* basics */
/**********/

/* main.c */
int			minishell(t_cmds *cmd_lst);
void		if_first_check(int *old_fds, t_cmds *cmd_struct,
				int previous_command_exists);

void	run_cmds_loop(t_cmds *cmd_lst);

/* mini_utils.c */
char		*user_input(void);
int			ft_strcmp(const char *s1, const char *s2);
int			check_builtin(char *cmd);
void		free_token(t_tokens **token);
t_cmds		*cmd_struct(char **envp, int prev);

/* mini_utils_2 */
char		*free_both_strjoin(char *s1, char *s2);
int			valid_input(char *input);
void		free_env(t_cmds *cmd);
void		fd_closing(int *old_fds, int *new_fds, t_cmds *cmd_struct);
char		*ft_strjoin_zero(char const *s1, char const *s2);

/* signals.c */
void		get_signals(void);
void		signal_child_active(void);
void		get_signals_child(void);

/* ft_error.c */
void		lex_error(char *token);
void		set_err(char *token, int err);
void		*set_exit_status(char *str, int err);
void		set_exit_void(char *str, int err);
int			set_exit_int(char *str, int err);

/**********/
/* execution */
/**********/

int	run_commands(t_cmds **cmd_lst, int *prev_par_num);
// int			run_commands(t_cmds **cmd_lst);
// void			run_commands(t_cmds *cmd_lst);
int			pipe_builtin(t_cmds *cmd_lst, int *old_fds, int *new_fds, int flag);
void		execute_redirect(int pid, int *old_fds,
				int *new_fds, t_cmds *cmd_lst);
void		execute_pipe(t_cmds *cmd_lst, int *old_fds, int *new_fds, int flag);
void		execute_child(int pid, int *old_fds, int *new_fds, t_cmds *cmd_lst);
int			is_builtin(t_cmds *cmd_lst);
int			is_builtin2(t_cmds *cmd_lst);
void		try_env(t_cmds *cmd_lst);
void		wait_for_children(int pid, int *waitpid_status, int err);
void		redirect_child(int *old_fds, int *new_fds,
				t_cmds *cmd_struct, int previous_command_exists);

/*******/
/* builtins */
/*******/

// builtin_pwd.c
void		pwd(void);

// builtin_cd.c
void		cd(t_cmds *cmd_lst);
char		*get_home_path(char **env_var);

// builtin_echo.c
void		echo(t_cmds *cmd_lst);

// builtin_env.c
void		env(t_cmds *cmd_lst);

// builtin_unset.c
void		unset(t_cmds *cmd_lst);
// int				valid_input_helper_unset(char *cur_cmd, int n);
int			valid_input_helper(char *cur_cmd, int n);

// builtin_exit.c
void		builtin_exit(t_cmds *cmd_lst);

/* builtin_export.c */
void		builtin_export(t_cmds *cmd);
char		**sort_export(char **expo);
char		*find_var(char **vars, char *var);
void		add_env(t_cmds *cmd, char *var);

/* builtin_export_2.c */
int			ft_var(char **vars, char	*var);
void		var_lst(t_cmds *cmd);
void		del_var(t_cmds *cmd, char *var);

/* builtin_export_3.c */
int			len_equal(char *var);
char		**put_quotes(char **expo);
void		export_without_args(t_cmds *cmd);
int			export_err(t_cmds *cmd, char *str, int i);

#endif
