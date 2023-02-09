/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mervyilm <mervyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:51:44 by mervyilm          #+#    #+#             */
/*   Updated: 2023/02/09 12:10:49 by mervyilm         ###   ########.fr       */
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
			schr[fd] = 0;
			return (NULL);
		}
		line = ft_substr(schr[fd], 0, ft_strlen(schr[fd]));
		free(schr[fd]);
		schr[fd] = 0;
	}
	else
	{
		line = ft_substr(schr[fd], 0, fin(1, schr[fd]));
		temp = schr[fd];
		schr[fd] = ft_substr(ft_strchr(schr[fd], '\n'), 1, fin(2, schr[fd]));
		free(temp);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*schr[256];
	char		*chr;

	chr= (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!chr)
		return (NULL);
	if (read(fd, chr, 0) == -1 || fd == -1 || BUFFER_SIZE < 1)
	{
		free(chr);
		free(schr);
		return (NULL);
	}
	read_line(chr, fd, schr);
	return (not_new_line(schr, fd));
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	char *str;
// 	int line = 0;
// 	int fd;
	
// 	//Finding total lines
// 	fd = open("a.txt", O_RDONLY, 0777);
// 	while((str = get_next_line(fd)) != NULL)
// 		line++;
// 	close(fd);

// 	//Finding first line
// 	fd = open("a.txt", O_RDONLY, 0777); 
// 	printf("Count of lines inside a.txt = %d\n", line);
// 	printf("First line = %s", get_next_line(fd));
// 	close(fd);

// 	//Finding a specific line
// 	fd = open("a.txt", O_RDONLY, 0777); 
// 	int i = 0;
// 	while(i++ < 1) // number line - 2
// 		get_next_line(fd); // 0 and 1 passed
		
// 	printf("3rd line = %s", get_next_line(fd)); // 2 which is 3 printed out
// 	close(fd);

// 	//Finding the last line
// 	fd = open("a.txt", O_RDONLY, 0777); 
// 	int j = 0;
// 	while(j++ < line)
// 		get_next_line(fd);
		
// 	printf("Last line = %s\n", get_next_line(fd));
// }
