/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mervyilm <mervyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:51:44 by mervyilm          #+#    #+#             */
/*   Updated: 2023/01/30 17:37:16 by mervyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

void	read_line(char *chr, int fd, char **schr)
{
	char	*temp;
	int		rd;

	if (!*schr || !ft_strchr(*schr, '\n'))
	{
		rd = read(fd, chr, 5);
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
			rd = read(fd, chr, 5);
		}
	}	
	free(chr);
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
			return (NULL);
		}
		line = ft_substr(*schr, 0, ft_strlen(*schr));
		free(*schr);
	}
	else
	{
		line = ft_substr(*schr, 0, ft_strlen(*schr) - ft_strlen(ft_strchr(*schr, '\n')) + 1);
		temp = *schr;
		*schr = ft_substr(ft_strchr(*schr, '\n'), 1, ft_strlen(ft_strchr(*schr, '\n')) - 1);
		free(temp);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*schr;
	char		*chr;

	chr = (char *)malloc(sizeof(char) * 100);
	if (!chr)
	{
		return (NULL);
		read_line(chr, fd, &schr);
	}
	return (not_new_line(&schr));
}

int	main(void)
{
	int	fd;

	fd = open("a.txt", O_CREAT | O_RDWR, 0777);
	write(fd, "ecocum\nonur", 11);
	close(fd);
	fd = open("a.txt", O_RDONLY, 0777);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}
