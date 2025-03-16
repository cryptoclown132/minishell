/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_innit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:08:57 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/16 22:16:27 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*innit_token(char *input, int *i, int token_type)
{
	t_tokens	*token;

	token = malloc(sizeof(t_tokens));
	if (!token)
		return (set_exit_status("Failed to Malloc", 1));
	token->type = token_type;
	token->token = input;
	token->next = NULL;
	if (token_type == OR || token_type == AND)
		*i += 1;
	return (token);
}

char	*itw_loop(char *input, char *tkn, int *j, char **envp)
{
	t_itw_loop	t;

	t.k = *j;
	t.tmp = '\0';
	if (input[t.k] == '"' || input[t.k] == '\'')
	{
		t.tmp = input[t.k++];
		while (input[t.k] != t.tmp)
			t.k++;
		t.tmp_str = ft_substr(input, *j + 1, t.k - *j - 1);
	}
	else
	{
		while (input[t.k] && input[t.k] != '\'' && input[t.k] != '"'
			&& input[t.k] != '\n' && input[t.k] != '|' && input[t.k] != '<'
			&& input[t.k] != '>' && input[t.k] != ' ' && input[t.k] != '&')
			t.k++;
		t.tmp_str = ft_substr(input, *j, t.k - *j);
		t.k--;
	}
	if (t.tmp != '\'')
		t.tmp_str = expander(t.tmp_str, envp);
	tkn = free_both_strjoin(tkn, t.tmp_str);
	*j = t.k + 1;
	return (tkn);
}

t_tokens	*init_token_word(char *input, int *i, char **envp, int para_num)
{
	int			j;
	char		*tkn;
	t_tokens	*token;

	j = *i;
	tkn = NULL;
	while (input[j] && input[j] != ' ' && input[j] != '|'
		&& input[j] != '<' && input[j] != '>' && input[j] != '&')
	{
		tkn = itw_loop(input, tkn, &j, envp);
		*i = j;
	}
	*i = j - 1;
	token = innit_token(tkn, i, WORD);
	if (ft_strchr(tkn, '=') && valid_input(tkn))
		token->type = EQUAL;
	
	token->parenthesis_num = para_num;
	
	return (token);
}

t_tokens	*init_redir(char *input, int *i, int type, char **envp, int para_num)
{
	t_tokens	*token;
	int			j;

	j = *i;
	if (type == IN || type == OUT)
		j++;
	else
		j += 2;
	*i = space_len(input, &j);
	token = init_token_word(input, &j, envp, para_num);
	token->type = type;
	*i = j;
	return (token);
}

void	add_token(t_tokens **token_lst, t_tokens *token)
{
	t_tokens	*first;

	first = *token_lst;
	if (*token_lst == NULL)
		*token_lst = token;
	else
	{
		while (first->next != NULL)
			first = first->next;
		first->next = token;
	}
}
