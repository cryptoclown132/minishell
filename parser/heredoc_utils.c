/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:41:01 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/07 18:17:59 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_dollar(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '$')
			return (1);
	}
	return (0);
}

void	here_doc_loop(t_tokens *token, int fd, char **env)
{
	t_here_loop	h;

	h.limiter = token->token;
	h.input = readline("> ");
	while (h.input && g_exit_status != 130)
	{
		if (ft_strcmp(h.input, h.limiter) == 0)
			break ;
		if (is_dollar(h.input))
		{
			h.tmp = h.input;
			h.input = get_var(h.tmp, env);
			write(fd, h.input, ft_strlen(h.input));
			write(fd, "\n", 1);
			free(h.tmp);
		}
		else
		{
			write(fd, h.input, ft_strlen(h.input));
			write(fd, "\n", 1);
		}
		free(h.input);
		h.input = readline("> ");
	}
	free(h.input);
}
