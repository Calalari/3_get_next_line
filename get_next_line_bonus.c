/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mervyilm <mervyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:51:44 by mervyilm          #+#    #+#             */
/*   Updated: 2023/02/13 12:34:24 by mervyilm         ###   ########.fr       */
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

char	*not_new_line(char **schr, int fd)
{
	char	*temp;
	char	*line;
	int		len_till_new ;

	if (!schr[fd])
		return (NULL);
	if (!ft_strchr(schr[fd], '\n'))
	{
		if (!ft_strlen(schr[fd]))
		{
			free(schr[fd]);
			schr[fd] = 0;
			return (NULL);
		}
		line = ft_substr(schr[fd], 0, ft_strlen(schr[fd]));
		free(schr[fd]);
		schr[fd] = 0;
		return (line);
	}
	len_till_new = ft_strlen(ft_strchr(schr[fd], '\n'));
	line = ft_substr(schr[fd], 0, ft_strlen(schr[fd]) - len_till_new + 1);
	temp = schr[fd];
	schr[fd] = ft_substr(ft_strchr(schr[fd], '\n'), 1,  ft_strlen(schr[fd]));
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
	if (read(fd, chr, 0) == -1 || BUFFER_SIZE < 1)
	{
		free(*schr);
		free(chr);
		return (NULL);
	}
	read_line(chr, fd, schr);
	return (not_new_line(schr, fd));
}

#include <fcntl.h>
#include <stdio.h>

int main()
{
	int		line;
	char	*str;
	char	*str1;

	int		fd;
	int		fd1;

	// Printing first line and line count
	fd = open("a.txt", O_RDONLY);
	fd1 = open("b.txt", O_RDONLY);

	str = get_next_line(fd);
	str1 = get_next_line(fd1);
	printf("First line of fd: %s\n", str);
	printf("First line of fd1: %s\n", str1);

	free(str);
	free(str1);
	close(fd);
	system("leaks a.out");
}
