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

t_tokens	*lexer(t_tokens *token_lst, char *input, char **envp)
{
	int			i;
	t_tokens	*token;

	token_lst = NULL;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '|' && input[i + 1] == '|') //i++
			token = innit_token(ft_strdup("||"), &i, OR);
		else if (input[i] == '|')
			token = innit_token(ft_strdup("|"), &i, PIPE);
		else if (input[i] == '&' && input[i + 1] == '&') // i++
			token = innit_token(ft_strdup("&&"), &i, AND);
		else if (input[i] == '<' && input[i + 1] != '<')
			token = innit_redir(input, &i, IN, envp);
		else if (input[i] == '<' && input[i + 1] == '<')
			token = innit_redir(input, &i, DOC, envp);
		else if (input[i] == '>' && input[i + 1] != '>')
			token = innit_redir(input, &i, OUT, envp);
		else if (input[i] == '>' && input[i + 1] == '>')
			token = innit_redir(input, &i, APP, envp);
		else if (input[i] != ' ')
			token = innit_token_word(input, &i, envp);
		if (input[i] != ' ')
			add_token(&token_lst, token);
	}
	return (token_lst);
}