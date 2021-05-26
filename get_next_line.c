/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:54:45 by alellouc          #+#    #+#             */
/*   Updated: 2021/05/26 19:39:19 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
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


void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*buffer;
	size_t			len;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	len = size * count;
	buffer = malloc(len);
	if (!buffer)
		return (NULL);
	while (len--)
		buffer[len] = 0;
	return ((void *)buffer);
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
	while (len_s1--)
		dest[len_s1] = s1[len_s1];
	return (dest);
}

void	*ft_strchr(const char *s, int c)
{
	char	*p_s;
	char	c_c;

	p_s = (char *)s;
	c_c = (char)c;
	while (*p_s)
		if (*p_s++ == c_c)
			return (p_s);
	return (NULL);
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*p_dst;
	unsigned const char	*p_src;
	unsigned char		cc;

	p_dst = dst;
	p_src = src;
	cc = c;
	while (n--)
	{
		*p_dst++ = *p_src;
		if (*p_src++ == cc)
		{
			*--p_dst = 0;
			return ((void *)p_src);
		}
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = (char *)malloc(sizeof(*dst) * (len_s1 + len_s2 + 1));
	if (dst == NULL)
		return (NULL);
	ft_memccpy(dst, s1, 0, len_s1);
	ft_memccpy((dst + len_s1), s2, 0, len_s2);
	dst[len_s1 + len_s2] = 0;
	free((void *)s1);
	return (dst);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	static char		buf[BUFFER_SIZE + 1] = {0};
	char	*newline;
	char		*tmp;
	char		*test;

	if (fd < 0 || fd > FOPEN_MAX || !line || BUFFER_SIZE < 1)
		return (-1);
	ret = ft_strlen(buf) + 1;
	newline = ft_calloc(sizeof(*newline), BUFFER_SIZE);
	while (ret > 0 && !ft_strchr(buf, '\n'))
	{
		if (!ft_strchr(buf, '\n'))
		{
			newline = ft_strjoin(newline, buf);
			ret = read(fd, buf, BUFFER_SIZE);
			if (ret == -1)
				return (-1);
			buf[ret] = 0;
		/*	printf("\033[1;31mret read : %d\033[0m\n", ret);*/
		}
	}
	if (!ret)
		free(newline);
	/*	return (0);*/
	else if (ret > 0)
	{
		tmp = ft_calloc(sizeof(*tmp), ret);
		test = ft_memccpy(tmp, buf, '\n', ret);
		*line = ft_strjoin(newline, tmp);
		free(tmp);
		ft_memccpy(buf, test, '\0', BUFFER_SIZE);
		ret = 1;
	}

	return (ret);
}

/* Uniquement pour le debugage */
int	main(int argc, char **argv)
{
	char	*line;
	size_t	fd;
	int		gnl;

	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		ft_putstr_fd(line, 1);
		ft_putstr_fd("\n", 1);
		free(line);
		printf("\n\033[1;33mretour gnl : %d\033[0m\n", gnl);
	}
	printf("\n\033[1;32mretour dernier gnl: %d\033[0m\n", gnl);
	ft_putstr_fd("\n", 1);
	printf("\n\033[1;34m%d\033[0m\n", FOPEN_MAX);
	close(fd);
	return (0);
}/**/
/* Fin debugage */
