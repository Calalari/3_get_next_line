/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mervyilm <mervyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:51:44 by mervyilm          #+#    #+#             */
/*   Updated: 2023/02/11 13:30:47 by mervyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_line(char *chr, int fd, char **schr)
{
	char	*temp;
	int		rd;

	if (!*schr || !ft_strchr(*schr, '\n'))
	{
		rd = read(fd, chr, BUFFER_SIZE);
		while (rd > 0)
		{
			chr[rd] = 0;
			if (!*schr)
				*schr = ft_substr(chr, 0, rd);
			else
			{
				temp = *schr;
				*schr = ft_strjoin(*schr, chr);
				free(temp);
			}
			if (ft_strchr(chr, '\n'))
				break ;
			rd = read(fd, chr, BUFFER_SIZE);
		}
	}
	free(chr);
}

static int	fin(int point, char **schr)
{
	if (point == 1)
		return (ft_strlen(*schr) - ft_strlen(ft_strchr(*schr, '\n')) + 1);
	if (point == 2)
		return (ft_strlen(ft_strchr(*schr, '\n')) - 1);
	return (0);
}

char	*not_new_line(char **schr)
{
	char	*temp;
	char	*line;

	if (!*schr)
		return (NULL);
	if (!ft_strchr(*schr, '\n'))
	{
		if (!ft_strlen(*schr))
		{
			free(*schr);
			*schr = 0;
			return (NULL);
		}
		line = ft_substr(*schr, 0, ft_strlen(*schr));
		free(*schr);
		*schr = 0;
		return (line);
	}
	line = ft_substr(*schr, 0, fin(1, schr));
	temp = *schr;
	*schr = ft_substr(ft_strchr(*schr, '\n'), 1, fin(2, schr));
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*schr;
	char		*chr;

	chr = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!chr)
		return (NULL);
	if (read(fd, chr, 0) == -1 || fd == -1 || BUFFER_SIZE < 1)
	{
		free(schr);
		free(chr);
		return (NULL);
	}
	read_line(chr, fd, &schr);
	return (not_new_line(&schr));
}

#include <fcntl.h>
#include <stdio.h>
int main()
{
	int		line;
	char		*str;
	int		fd;

	fd = open("a.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("First line: %s", str);
	free(str);
	line = 1;
	while ((str = get_next_line(fd)))
	{
		free(str);
		++line;
	}
	printf("Count Line: %d\n", line);
	close(fd);

	fd = open("a.txt", O_RDONLY);
	int	j;

	j = -1;
	while (++j < line)
	{
		str = get_next_line(fd);
		free(str);
	}
	printf("Last line %s\n", str);
	//system("leaks a.out");
}
