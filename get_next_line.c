/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:54:45 by alellouc          #+#    #+#             */
/*   Updated: 2021/05/23 20:20:02 by alellouc         ###   ########.fr       */
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
	if (ft_strlen(s1) > 0)
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
/*	static char *buf = NULL;*/
	char		buf[BUFFER_SIZE + 1];
	/*static char	*endline = NULL;*/
	static char	*newline;
/*	char		*tmp;*/
/*	int			i;*/

/*	ssize_t		r;
	char		bf[BUFFER_SIZE + (r = 1)];
	static char	*c_line = NULL;
	char		*tmp;

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
		*line = ft_substr(c_line, 0, ((char *)ft_strchr(c_line, '\n') - c_line));
	else
		return (-1);
	tmp = ft_strdup(c_line + (ft_strlen(*line) + ((r > 0) ? +1 : +0)));
	ft_memdel((void **)&c_line);
	c_line = tmp;
	return (r == 0 ? 0 * ft_memdel((void **)&c_line) : 1);*/
	
	if (fd < 0 || fd > FOPEN_MAX || !line || BUFFER_SIZE < 1)
		return (-1);
	/*if (!newline)
		newline = ft_calloc(sizeof(*newline), 1);
	else
		*line = ft_strdup(newline);*/
	if (newline)
		printf("\t\033[1;31mnewline - debut: %s\033[0m\n", newline);
	buf[0] = 0;
	ret = 1;
	while (!ft_strchr(newline, '\n') && read(fd, buf, BUFFER_SIZE) > 0)
	{
		buf[BUFFER_SIZE] = 0;
		ret = ft_strlen(buf);
		newline = ft_strjoin(newline, buf);

	/*	printf("\033[1;31m\tbuf : %s\033[0m\n", buf);
		printf("\033[1;31m\tsize buf : %d\033[0m\n", ret);
		printf("\tnewline : %s\n", newline);*/
	}
	if (ret == 0 || !ft_strlen(buf))
	{
	/*	*line = ft_strdup(newline);
		free(newline);*/
		return (0);
	}
	else if (ret == -1)
		return (-1);
	else
	{
		/* Scinder "buf" en deux parties :
		** celle avant \n, qui doit aller dans line
		** celle apres \n, qui doit aller dans la variable statique */
		/*newline = ft_strjoin(newline, buf);*/
		*line = ft_strdup(newline);
		free(newline);
		newline = ft_strchr(buf, '\n');
		if (newline)
			printf("\t\033[1;31mnewline: %s\033[0m\n", newline);
		printf("\n\t\033[1;35mbuf: %s\033[0m\n", buf);
	/*	*line = ft_substr(newline, 0, ((char *)ft_strchr(newline, '\n') -
	**	newline));*/
	/*	return (1);*/
	}
/*	tmp = ft_strdup(newline + (ft_strlen(*line) + ((r > 0) ? +1 : +0)));*/
/*	ft_memdel((void **)&c_line);*/
/*	free(newline);*/
/*	newline = tmp;
	free(tmp);*/
	return (1);
	
/*	if (!line || BUFFER_SIZE < 1 || fd < 0)
		return (-1);
	i = 0;
	newline = NULL;
	if (buf)
		*line = ft_strdup(buf);
	else
		*line = ft_strdup("");
	while (!newline)
	{
		buf = (char *)malloc(sizeof(*buf) * BUFFER_SIZE);
		ret = read(fd, buf, BUFFER_SIZE);
		newline = ft_memchr(buf, '\n', ft_strlen(buf));
		if (newline && ret > 0)
		{
			newline++;
			newline = ft_strdup(newline);
			i = ret - ft_strlen(newline);

			while (ret--)
			{
				if (i <= ret)
					buf[ret] = 0;
			}
			printf("\nret si newline : %d\n", ret);
			ret = 1;*/

			/* Debug */
		/*	ft_putstr_fd("\nPour voir ce que donne la newline 1 : \033[1;31m", 1);
			ft_putstr_fd(newline, 1);
			ft_putstr_fd("\033[0m", 1);
			ft_putstr_fd("\nbuf contient : \033[0;36m", 1);
			ft_putstr_fd(buf, 1);
			ft_putstr_fd("\033[0m", 1);*/
			/* Fin Debug */

		/*	*line = ft_strjoin(*line, buf); 
			buf = ft_strdup(newline);*/
			/*buf =*//* ft_memcpy(buf, newline, BUFFER_SIZE);*/
/*			ft_memcpy(buf, newline, ft_strlen(buf));*/

			/* Debug */
		/*	ft_putstr_fd("Pour voir ce que donne la newline 2: \033[1;31m", 1);
			ft_putstr_fd(newline, 1);
			ft_putstr_fd("\033[0m", 1);
			ft_putstr_fd("\nbuf contient : \033[0;36m", 1);
			ft_putstr_fd(buf, 1);
			ft_putstr_fd("\033[0m", 1);*/
			/* Fin Debug */

		/*	free(newline);*/
	/*	}*/
/*		else
		{
			*line = ft_strjoin(*line, buf);
		}
	}*/
	/* Debug */
/*	ft_putstr_fd("\nbuf final contient : \033[0;36m", 1);
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\033[0m", 1);ft_putstr_fd("\nDans la line, on a : \033[1;32m", 1);
	ft_putstr_fd(*line, 1);
	ft_putstr_fd("\033[0m", 1);*/
	/* Fin Debug */
	

/*	if (ret > 0 || newline)
		ret = 1;
	if (ret == 0)
		free(buf);
	printf("\nret : %d\n", ret);
	return (ret);*/
}

/* Uniquement pour le debugage */
int	main(int argc, char **argv)
{
	char	*line;
	size_t	fd;
	int		gnl;
/*	int		i = 0;*/

	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	gnl = 1;
	while (gnl == 1)
/*	while (i++ <= 15)*/
	{
		gnl = get_next_line(fd, &line);
		ft_putstr_fd(line, 1);
	/*	ft_putstr_fd("\n", 1);*/
	/*	printf(" gnl = %d\n", gnl);*/
	}
		ft_putstr_fd("\n", 1);
		printf(" gnl = %d\n", gnl);
	free(line);
	close(fd);
	return (0);
}
/* Fin debugage */
