/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:54:45 by alellouc          #+#    #+#             */
/*   Updated: 2021/05/31 10:25:26 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
/* Uniquement pour le debugage */
#include <stdio.h>
/*#include <fcntl.h>*/

/*void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}*/
/* Fin debugage */

/* Fonctions utilisées par méthode sv */
/* char	*ft_strnew(size_t size)
{
	return (ft_calloc(sizeof(char), (size + 1)));
}

int		ft_memdel(void **ptr)
{
	unsigned int	i;

	i = 0;
	if (*ptr)
	{
		while (ptr[i])
		{
			ptr[i] = 0;
		}
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
*char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s || (long int)len < 0)
		return (NULL);
	ptr = (char *)malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	while (start < ft_strlen(s) && i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = 0;
	return (ptr);
}*/

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
/* 2e essai qui ne passe pas les testeurs */
	int			ret;
	static char		buf[BUFFER_SIZE + 1];
	char	*newline;
	char		*tmp;
	char		*test;

	if (fd < 0 || fd > FOPEN_MAX || !line || BUFFER_SIZE < 1)
		return (-1);
	ret = ft_strlen(buf) + 1;
	newline = ft_strdup("");
	while (ret > 0 && !ft_strchr(buf, '\n'))
	{
		if (!ft_strchr(buf, '\n'))
		{
			newline = ft_strjoin(newline, buf);
			ret = read(fd, buf, BUFFER_SIZE);
			if (ret < 0)
				return (-1);
			buf[ret] = 0;
		}
	}
	if (!ret && !ft_strlen(newline))
	{
		free(newline);
	}
	else if (ret > 0 || ft_strlen(newline))
	{
		tmp = ft_calloc(sizeof(*tmp), ret + 1);
		test = ft_memccpy(tmp, buf, '\n', ret);
		*line = ft_strjoin(newline, tmp);
		free(tmp);
		if (test)
			ft_memccpy(buf, test, '\0', BUFFER_SIZE);
		ret = 1;
	}
	return (ret);

/* Version sv */
/*	ssize_t		r;
	char	bf[BUFFER_SIZE + (r = 1)];
	static char	*c_line = NULL;
	char	*tmp;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	c_line == NULL ? c_line = ft_strnew(0) : NULL;
	while (!ft_strchr(c_line, '\n') && (r = read(fd, bf, BUFFER_SIZE)) > 0)
	{
		bf[r] = 0;
		tmp = ft_strjoin(c_line, bf);
		ft_memdel((void **)&c_line);
		c_line = tmp;
	}
	if (r == 0)
		*line = ft_strdup(c_line);
	else if (r > 0)
		*line = ft_substr(c_line, 0, (ft_strchr(c_line, '\n') - c_line));
	else
		return (-1);
	tmp = ft_strdup(c_line + (ft_strlen(*line) + ((r > 0) ? +1 : +0)));
	ft_memdel((void **)&c_line);
	c_line = tmp;
	return (r == 0 ? 0 * ft_memdel((void **)&c_line) : 1);*/
}

/* Uniquement pour le debugage */
/*int	main(int argc, char **argv)
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
	}
	close(fd);
	return (0);
}*/
/* Fin debugage */
