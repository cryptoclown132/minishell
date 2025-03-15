/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 20:37:34 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/20 22:10:12 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_input_helper(char *cur_cmd, int n)
{
	if (!n)
	{
		if (!ft_isalpha(cur_cmd[n]) && !ft_strchr(cur_cmd, '_')
			&& !ft_strchr(cur_cmd, '\"') && !ft_strchr(cur_cmd, '\''))
		{
			set_exit_status("Error", 1);
			return (0);
		}
		return (1);
	}
	else
	{
		if (!ft_isalnum(cur_cmd[n]) && !ft_strchr(cur_cmd, '_')
			&& !ft_strchr(cur_cmd, '\"') && !ft_strchr(cur_cmd, '\''))
		{
			set_exit_status("Error", 1);
			return (0);
		}
		return (1);
	}
}
