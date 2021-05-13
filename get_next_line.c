/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:54:45 by alellouc          #+#    #+#             */
/*   Updated: 2021/05/13 14:55:25 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/* Uniquement pour le debugage */
#include <stdio.h>
#include <fcntl.h>

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}
/* Fin debugage */

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	size_t	len_s1;
	char	*dest;

	len_s1 = ft_strlen(s1);
	dest = (char *)malloc((len_s1 + 1) * sizeof(*dest));
	if (!dest)
	{
		errno = ENOMEM;
		return ((char *)0);
	}
	dest[len_s1] = 0;
	while(len_s1--)
		dest[len_s1] = s1[len_s1];
	return (dest);
}

int	get_next_line(int fd, char **line)
{
	int	ret;
	static char buf[BUFFER_SIZE + 1];

	/*if (ft_strlen(buf) >= BUFFER_SIZE + 1)
		ret = read(fd, &buf[ft_strlen(buf)], BUFFER_SIZE - ft_strlen(buf));
	else*/
		ret = read(fd, buf, BUFFER_SIZE);
	/*printf("\nret = %d", ret);*/
/*	printf(" ret = %d\n", ret);*/
	if (ret > 0)
		ret = 1;
	if (ret == 0)
		*buf = 0;
	/*if (ret == BUFFER_SIZE)
		get_next_line(fd, line);*/
	*line = ft_strdup(buf);
	return (ret);
}

/* Uniquement pour le debugage */
int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	char	*line;
	int		fd;
	int		gnl;

/*	fd = open("test_file.txt", O_RDONLY);*/
	fd = 0;
	gnl = 1;
	while (gnl == 1)
	{
		gnl = get_next_line(fd, &line);
		ft_putstr_fd(line, 1);
	/*	ft_putstr_fd("\n", 1);*/
	/*	printf(" gnl = %d\n", gnl);*/
	}
	free(line);
	close(fd);
	return (0);
}
/* Fin debugage */
