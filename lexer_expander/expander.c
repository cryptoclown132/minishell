/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:01:04 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/12 17:42:04 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expander(char *token, char **envp)
{
	t_expan	e;

	e.i = -1;
	e.tmp_var = NULL;
	while (token[++e.i])
	{
		if (token[e.i] == '$' && token[e.i + 1] != ' '
			&& token[e.i + 1] != '\0')
		{
			e.tmp_var = get_var(token, envp);
			free(token);
			break ;
		}
	}
	if (e.tmp_var == NULL)
		e.tmp_var = token;
	return (e.tmp_var);
}
