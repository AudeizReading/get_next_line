/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:54:45 by alellouc          #+#    #+#             */
/*   Updated: 2021/05/24 19:55:38 by alellouc         ###   ########.fr       */
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

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p_b;
	unsigned char	cc;

	p_b = b;
	cc = c;
	while (len--)
		*p_b++ = cc;
	return (b);
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
	ft_memset(buffer, '\0', len);
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
/*	free((void *)s1);*/
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

void	*ft_strchr(const char *s, int c)
{
	char	*p_s;
	char	c_c;

	p_s = (char *)s;
	c_c = (char)c;
	while (*p_s)
		if (*p_s++ == c_c)
			return (--p_s);
	if (*p_s == c_c)
		return (p_s);
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
/*	free((void *)p_dst);
	free((void *)p_src);*/
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_tmp;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = (char *)malloc(sizeof(*dst) * (len_s1 + len_s2 + 1));
	if (dst == NULL)
		return (NULL);
	len_tmp = len_s1;
	while (len_tmp--)
		dst[len_tmp] = s1[len_tmp];
	len_tmp = len_s2;
	while (len_tmp--)
		dst[len_s1 + len_tmp] = s2[len_tmp];
/*ft_memcpy(dst, s1, len_s1);
ft_memcpy((dst + len_s1), s2, len_s2);*/
	dst[len_s1 + len_s2] = 0;
/*	if (ft_strlen(s1) > 0)
		free((void *)s1);*/
	free((void *)s1);
/*	free((void *)s2);*/ /* On l'utilisera si je me decide a utiliser buf comme un pointeur*/
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	len_s;

	len_s = ft_strlen(s);
	if (len > len_s)
		len = len_s;
	if (len + start > len_s && start < len_s)
		len = len_s - start;
	if (start >= len_s)
		len = 0;
	dst = (char *)malloc(sizeof(*dst) * (len + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s + start, len);
	free((void *)s);
	return (dst);
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
			/**--p_dst = 0;*/
			*(unsigned char *)(dst + (p_dst - (unsigned char *)dst) - 1) = 0;
		/*	printf("\n\033[33mp_dst de memccpy: %s\033[0m\n", dst);*/
			return (p_dst);
		}
	}
	return (NULL);
}

char	*ft_strnew(size_t size)
{
	return (ft_calloc(sizeof(char), size + 1));
}

int		ft_memdel(void **ptr)
{
	if (*ptr)
	{
		ft_memset(*ptr, 0, ft_strlen(*ptr));
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	static char		buf[BUFFER_SIZE + 1];
	char	*newline;
	char		*tmp;

	if (fd < 0 || fd > FOPEN_MAX || !line || BUFFER_SIZE < 1)
		return (-1);
	if (ft_strchr(buf, '\n'))
	{
		newline = ft_calloc(sizeof(*newline), ft_strlen(buf));
		tmp = ft_calloc(sizeof(*tmp), ft_strlen(buf));
		ft_memccpy(tmp, buf, '\n', ft_strlen(buf));
		newline = ft_strjoin(newline, tmp);
		*line = ft_strdup(newline);
		free(newline);
		free(tmp);
		newline = ft_strchr(buf, '\n');
		newline++;
		ft_memcpy(buf, newline, BUFFER_SIZE);
		return (1);
	}
	else
		newline = ft_strdup(buf);

	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0 && !ft_strchr(buf, '\n'))
	{
		buf[BUFFER_SIZE] = 0;
		newline = ft_strjoin(newline, buf);
	}
	if (ret == 0)
	{
		/* Ici ca pose des soucis pour le fd 0 car le 0 n'est jamais atteint, il
		** y a toujours un \n qui est compté */
		printf("\033[1;33mHello, this is the end\033[0m");
		return (0);
	}
	else if (ret == -1)
		return (-1);
	else
	{
		tmp = ft_calloc(sizeof(*tmp), ft_strlen(buf));
		ft_memccpy(tmp, buf, '\n', ft_strlen(buf));
		newline = ft_strjoin(newline, tmp);
		*line = ft_strdup(newline);
		free(newline);
		free(tmp);
		newline = ft_strchr(buf, '\n');
		newline++;
		ft_memcpy(buf, newline, BUFFER_SIZE);
	}
	return (1);
}

/* Uniquement pour le debugage */
int	main(int argc, char **argv)
{
	char	*line;
	size_t	fd;
	int		gnl;
/*	int		i = 30;*/

	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	while ((gnl = get_next_line(fd, &line)))
	{
		ft_putstr_fd(line, 1);
		free(line);
	}
	ft_putstr_fd("\n", 1);
	close(fd);
	return (0);
}
/* Fin debugage */
