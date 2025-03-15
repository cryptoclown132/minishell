/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 00:43:18 by fjerinic          #+#    #+#             */
/*   Updated: 2023/03/19 20:32:47 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_cmds *cmd_struct)
{
	int		i;

	i = 0;
	while (cmd_struct->env[i])
	{
		if (!ft_strncmp(cmd_struct->env[i], "_=", 2))
		{
			free(cmd_struct->env[i]);
			cmd_struct->env[i] = ft_strdup("_=usr/bin/env");
		}
		if (ft_strchr(cmd_struct->env[i], '='))
			ft_printf("%s\n", cmd_struct->env[i]);
		i++;
	}
}
