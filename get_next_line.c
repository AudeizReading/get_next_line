/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:54:45 by alellouc          #+#    #+#             */
/*   Updated: 2021/05/18 12:25:14 by alellouc         ###   ########.fr       */
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

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;
	unsigned char	c_c;

	p_s = (unsigned char *)s;
	c_c = (unsigned char)c;
	while (n--)
		if (*p_s++ == c_c)
			return (--p_s);
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*p_dst;
	unsigned const char	*p_src;

	p_dst = dst;
	p_src = src;
	if (!p_dst && !p_src)
		return ((void *)0);
	while (n--)
		*p_dst++ = *p_src++;
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len_s1;
	size_t	len_s2;
/*	size_t	len_tmp;*/

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = (char *)malloc(sizeof(*dst) * (len_s1 + len_s2 + 1));
	if (dst == NULL)
		return (NULL);
/*	len_tmp = len_s1;
	while (len_tmp--)
		dst[len_tmp] = s1[len_tmp];
	len_tmp = len_s2;
	while (len_tmp--)
		dst[len_s1 + len_tmp] = s2[len_tmp];*/
	ft_memcpy(dst, s1, len_s1);
	ft_memcpy((dst + len_s1), s2, len_s2);
	dst[len_s1 + len_s2] = 0;
	return (dst);
}

int	get_next_line(int fd, char **line)
{
	int	ret;
	static char buf[BUFFER_SIZE + 1];

	*line = "";
	while (!ft_memchr(buf, '\n', ft_strlen(buf)))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		*line = ft_strjoin(*line, buf);
	}
	/*printf("\nret = %d", ret);*/
/*	printf(" ret = %d\n", ret);*/
	if (ret > 0)
		ret = 1;
	if (ret == 0)
		*buf = 0;
	/**line = ft_strdup(buf);*/
/*	*line = ft_strjoin(*line, buf);*/
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
/*	gnl = 1;
	while (gnl == 1)
	{*/
	gnl = get_next_line(fd, &line);
	ft_putstr_fd(line, 1);
	/*	ft_putstr_fd("\n", 1);*/
	/*	printf(" gnl = %d\n", gnl);*/
/*	}*/
	free(line);
	close(fd);
	return (0);
}
/* Fin debugage */
