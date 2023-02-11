/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mervyilm <mervyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:51:44 by mervyilm          #+#    #+#             */
/*   Updated: 2023/02/11 15:37:38 by mervyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	read_line(char *chr, int fd, char **schr)
{
	char	*temp;
	int		rd;

	if (!*schr || !ft_strchr(*schr, '\n'))
	{
		rd = read(fd, chr, BUFFER_SIZE);
		printf("1) rd value: %d\n", rd);
		while (rd > 0)
		{
			chr[rd] = 0;
			printf("2) chr value: %s\n", chr);
			if (!*schr)
			{
				*schr = ft_substr(chr, 0, rd);
				printf("3) schr value: %s\n", *schr);
			}
			else
			{
				temp = *schr;
				*schr = ft_strjoin(*schr, chr);
				printf("4) schr value on join: %s\n", *schr);
				free(temp);
			}
			if (ft_strchr(chr, '\n'))
				break ;
			rd = read(fd, chr, BUFFER_SIZE);
		rd = read(fd, chr, BUFFER_SIZE);
		printf("5) rd value at last: %d\n", rd);
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
		printf("6) current line value: %s\n", line);
		free(*schr);
		*schr = 0;
		return (line);
	}
	line = ft_substr(*schr, 0, fin(1, schr));
	printf("7) line value before newline: %s\n", line);
	temp = *schr;
	*schr = ft_substr(ft_strchr(*schr, '\n'), 1, fin(2, schr));
	printf("8) schr value after newline: %s\n", *schr);
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

int main()
{
	int		line;
	char	*str;
	int		fd;

	// Printing first line and line count
	fd = open("a.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("First line: %s", str);
	free(str);
	line = 1;
	while ((str = get_next_line(fd)))
	{
		free(str);
		line++;
	}
	printf("Line count: %d\n", line);
	close(fd);

	// Finding last line
	fd = open("a.txt", O_RDONLY);
	int	j;

	j = 0;
	while (j++ < line)
	{
		str = get_next_line(fd);
		free(str);
	}
	printf("Last line %s\n", str);
	//system("leaks a.out");
}
