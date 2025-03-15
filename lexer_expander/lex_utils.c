/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:16:13 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/12 17:38:39 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_len(char *s, int *i)
{
	char	quote;
	int		tmp;

	tmp = *i;
	*i = ft_strlen(s);
	if (tmp < *i)
		quote = s[tmp++];
	while (tmp < *i && s[tmp] != quote)
		tmp++;
	*i = tmp;
	return (*i);
}

int	space_len(char *s, int *i)
{
	char	space;
	int		tmp;

	tmp = *i;
	if (s[tmp] != ' ')
	{
		*i = tmp;
		return (*i);
	}
	space = s[tmp];
	while (s[tmp] == space)
	{
		tmp++;
	}
	*i = tmp;
	return (*i);
}

int	without_quote(char *s, int *i)
{
	char	*pipe_red;
	int		j;
	int		tmp;

	tmp = *i - 1;
	pipe_red = "<>| ";
	while (s[++tmp])
	{
		j = -1;
		while (pipe_red[++j])
		{
			if (s[tmp] == pipe_red[j])
				break ;
		}
		if (s[tmp] == pipe_red[j])
			break ;
	}
	*i = tmp;
	return (tmp);
}

int	word_len(char *s, int *i)
{
	int		tmp;

	tmp = *i;
	if (s[tmp - 1] == '\'' || s[tmp - 1] == '"')
	{
		tmp--;
		quote_len(s, &tmp);
	}
	else
		without_quote(s, &tmp);
	*i = tmp;
	return (*i);
}
