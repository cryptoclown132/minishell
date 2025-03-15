/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:23:33 by jkroger           #+#    #+#             */
/*   Updated: 2022/07/28 18:31:55 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*cut_line(char *line)
{
	char	*output;
	int		i;

	output = ft_strchr(line, '\n');
	if (!output)
	{
		free(line);
		return (0);
	}
	i = 0;
	if (output[++i])
		output = ft_strdup(&output[i]);
	else
		output = NULL;
	free(line);
	return (output);
}

static char	*add_line(char *buff, char *line)
{
	if (!line)
		line = ft_strdup(buff);
	else
		line = edited_strjoin(line, buff);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*line[10240];
	char			*output;
	char			buff[BUFFER_SIZE + 1];
	int				size;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	if (size == -1)
		return (NULL);
	buff[size] = '\0';
	while (size > 0)
	{
		line[fd] = add_line(buff, line[fd]);
		if (ft_strchr(line[fd], '\n'))
			break ;
		size = read(fd, buff, BUFFER_SIZE);
		buff[size] = '\0';
	}
	output = ft_substr(line[fd], 0, ft_strlen(line[fd])
			- ft_strlen(ft_strchr(line[fd], '\n')) + 1);
	line[fd] = cut_line(line[fd]);
	return (output);
}
