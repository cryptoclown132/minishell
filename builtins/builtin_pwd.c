/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 00:45:37 by fjerinic          #+#    #+#             */
/*   Updated: 2023/03/13 00:45:51 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	char	path_ptr[PATH_SIZE];

	if (!getcwd(path_ptr, PATH_SIZE))
	{
		perror("Error");
		return ;
	}
	ft_printf("%s\n", path_ptr);
}
