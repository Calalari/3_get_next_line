/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mervyilm <mervyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:51:44 by mervyilm          #+#    #+#             */
/*   Updated: 2023/02/09 17:40:02 by mervyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	read_line(char *chr, int fd, char **schr)
{
	char	*temp;
	int		rd;

	if (!schr[fd] || !ft_strchr(schr[fd], '\n'))
	{
		rd = read(fd, chr, BUFFER_SIZE);
		while (rd > 0)
		{
			chr[rd] = 0;
			if (!schr[fd])
				schr[fd] = ft_substr(chr, 0, rd);
			else
			{
				temp = schr[fd];
				schr[fd] = ft_strjoin(schr[fd], chr);
				free(temp);
			}
			if (ft_strchr(chr, '\n'))
				break ;
			rd = read(fd, chr, BUFFER_SIZE);
		}
	}	
	free(chr);
}

static int	fin(int point, char *schr)
{
	if (point == 1)
		return (ft_strlen(schr) - ft_strlen(ft_strchr(schr, '\n')) + 1);
	if (point == 2)
		return (ft_strlen(ft_strchr(schr, '\n')) - 1);
	return (0);
}

char	*not_new_line(char **schr, int fd)
{
	char	*temp;
	char	*line;

	if (!schr[fd])
		return (NULL);
	if (!ft_strchr(schr[fd], '\n'))
	{
		if (!ft_strlen(schr[fd]))
		{
			free(schr[fd]);
			return (NULL);
		}
		line = ft_substr(schr[fd], 0, ft_strlen(schr[fd]));
		free(schr[fd]);
		schr[fd] = 0;
		return (line);
	}
	line = ft_substr(schr[fd], 0, fin(1, schr[fd]));
	temp = schr[fd];
	schr[fd] = ft_substr(ft_strchr(schr[fd], '\n'), 1, fin(2, schr[fd]));
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*schr[256];
	char		*chr;

	chr = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!chr)
		return (NULL);
	if (read(fd, chr, 0) == -1 || fd == -1 || BUFFER_SIZE < 1)
	{
		free(*schr);
		free(chr);
		return (NULL);
	}
	read_line(chr, fd, schr);
	return (not_new_line(schr, fd));
}
