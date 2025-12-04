/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkrati <wkrati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:27:38 by wkrati            #+#    #+#             */
/*   Updated: 2025/11/30 23:08:49 by wkrati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

static char	*get_line(char *leftover)
{
	size_t	i;
	size_t	l;
	char	*line;

	i = 0;
	l = 0;
	if (!leftover || !leftover[0])
		return (NULL);
	while (leftover[l] && leftover[l] != '\n')
		l++;
	if (leftover[l] == '\n')
		line = malloc(sizeof(char) * (l + 2));
	else
		line = malloc(sizeof(char) * (l + 1));
	if (!line)
		return (NULL);
	while (i < l)
	{
		line[i] = leftover[i];
		i++;
	}
	if (leftover[l] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*get_leftover(char *buff)
{
	size_t	i;
	size_t	l;
	size_t	n;
	char	*leftover;

	i = 0;
	n = 0;
	while (buff[n] && buff[n] != '\n')
		n++;
	if (buff[n] == '\0' || (buff[n] == '\n' && buff[n + 1] == '\0'))
		return (ft_free(buff), NULL);
	n++;
	l = ft_strlen(buff + n);
	leftover = malloc(sizeof(char) * (l + 1));
	if (!leftover)
		return (ft_free(buff), NULL);
	while (buff[n])
		leftover[i++] = buff[n++];
	leftover[i] = '\0';
	return (ft_free(buff), leftover);
}

static char	*get_read(int fd, char *buff)
{
	char	*readb;
	ssize_t	r;

	readb = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!readb)
		return (NULL);
	while (1)
	{
		r = read(fd, readb, BUFFER_SIZE);
		if (r < 0)
			return (ft_free(readb), ft_free(buff), NULL);
		if (!r)
			break ;
		readb[r] = '\0';
		buff = ft_strjoin(buff, readb);
		if (!buff)
			return (ft_free(readb), NULL);
		if (ft_strchr(readb, '\n'))
			break ;
	}
	ft_free(readb);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	buff = get_read(fd, buff);
	if (!buff)
		return (NULL);
	line = get_line(buff);
	buff = get_leftover(buff);
	if (!buff)
		ft_free(buff);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/