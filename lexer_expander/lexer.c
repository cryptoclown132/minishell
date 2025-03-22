/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:11:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/13 18:58:15 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	which_parenthesis(char parenthesis, int *i, int *para_num)
{
	*i += 1;
	if (parenthesis == '(')
		return true;
	*para_num += 1;
	return false;

}

t_tokens	*lexer(t_tokens *token_lst, char *input, char **envp)
{
	int			i;
	t_tokens	*token;

	token_lst = NULL;
	i = -1;

	int		para_num = 0;
	bool	open_para = false;
	while (input[++i])
	{
		if (input[i] == '(' || input[i] == ')')
			open_para = which_parenthesis(input[i], &i, &para_num);
		if (input[i] == '|' && input[i + 1] == '|') //i++
			token = init_token(ft_strdup("||"), &i, OR);
		else if (input[i] == '|')
			token = init_token(ft_strdup("|"), &i, PIPE);
		else if (input[i] == '&' && input[i + 1] == '&') // i++
			token = init_token(ft_strdup("&&"), &i, AND);
		else if (input[i] == '<' && input[i + 1] != '<')
			token = init_redir(input, &i, IN, envp, para_num);
		else if (input[i] == '<' && input[i + 1] == '<')
			token = init_redir(input, &i, DOC, envp, para_num);
		else if (input[i] == '>' && input[i + 1] != '>')
			token = init_redir(input, &i, OUT, envp, para_num);
		else if (input[i] == '>' && input[i + 1] == '>')
			token = init_redir(input, &i, APP, envp, para_num);
		else if (input[i] != ' ')
		{
			token = init_token_word(input, &i, envp, para_num); // echo )
			if (open_para == false)
				para_num++;
		}
		if (input[i] != ' ')
			add_token(&token_lst, token);
	}
	return (token_lst);
}
