/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:51:29 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/16 15:45:33 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_finder(char **envp, char *var)
{
	int	i;
	int	j;

	i = 0;
	var = edited_strjoin(var, "=");
	if (!var)
		return (set_exit_status("Failed to Malloc", 1));
	while (envp[i])
	{
		if (ft_strnstr(envp[i], var, ft_strlen(var)))
		{
			j = ft_strlen(var);
			free(var);
			return (ft_substr(envp[i], j, ft_strlen(envp[i]) - j + 1));
		}
		i++;
	}
	free(var);
	return (NULL);
}

void	var_exist(char *token, char **envp, int *i, char **var_value)
{
	int		j;

	j = *i + 1;
	while ((token[j] >= 'a' && token[j] <= 'z')
		|| (token[j] >= 'A' && token[j] <= 'Z')
		|| (token[j] >= '0' && token[j] <= '9'))
		j++;
	if ((j - *i) == 1 && token[j] != '?')
	{
		while (token[j] && token[j + 1] != '$')
			j++;
		*var_value = ft_substr(token, *i, j - *i);
	}
	else if (token[*i] == '$' && token[*i + 1] == '?')
	{
		*var_value = ft_itoa(g_exit_status);
		j++;
	}
	else
		*var_value = var_finder(envp, ft_substr(token, *i + 1, j - *i - 1));
	*i = j;
}

int	get_len(char *token, char **envp)
{
	int		i;
	int		var_len;
	char	*var_value;

	i = -1;
	var_len = 0;
	while (token[++i])
	{
		if (token[i] != '$')
			var_len++;
		if (token[i] == '$' && token[i + 1] != '$')
		{
			var_exist(token, envp, &i, &var_value);
			var_len += ft_strlen(var_value);
			free(var_value);
			i--;
		}
	}
	return (var_len);
}

char	*get_var(char *token, char **envp)
{
	t_get_var	e;

	e.var_value = malloc((get_len(token, envp) + 1) * sizeof(char));
	if (!e.var_value)
		return (set_exit_status("Failed to Malloc", 1));
	e.i = 0;
	e.j = 0;
	while (token[e.i])
	{
		if (token[e.i] == '$' && token[e.i + 1] != '$')
		{
			var_exist(token, envp, &e.i, &e.tmp);
			e.k = 0;
			if (e.tmp)
			{
				while (e.tmp[e.k])
					e.var_value[e.j++] = e.tmp[e.k++];
				free(e.tmp);
			}
		}
		else
			e.var_value[e.j++] = token[e.i++];
	}
	e.var_value[e.j] = '\0';
	return (e.var_value);
}
