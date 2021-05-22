/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:54:45 by alellouc          #+#    #+#             */
/*   Updated: 2021/05/22 11:54:11 by alellouc         ###   ########.fr       */
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

int	get_next_line(int fd, char **line)
{
/*	First try that sucks, but don't want to forget what i've done if my second
**	try isn't as so marvellous as i think */
	int			ret;
	static char buf[BUFFER_SIZE];
	char		*newline;
	int			i;

	
	if (!line || BUFFER_SIZE < 1 || fd < 0)
		return (-1);
	i = 0;
	newline = NULL;
	*line = ft_strdup(buf);
	while (!newline)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		newline = ft_memchr(buf, '\n', ft_strlen(buf));
		if (newline)
		{
			newline++;
			newline = ft_strdup(newline);
		/*	i = ft_strlen(buf) - ft_strlen(newline);*/
			i = ret - ft_strlen(newline);

			while (ret--)
			{
				if (i <= ret)
					buf[ret] = 0;
			/*	ft_putstr_fd("\n(boucle while(ret--)) buf contient : \033[0;36m", 1);
				ft_putstr_fd(buf, 1);
				ft_putstr_fd("\033[0m", 1);*/

			}
			ret = 1;
			ft_putstr_fd("\nPour voir ce que donne la newline 1 : \033[1;31m", 1);
			ft_putstr_fd(newline, 1);
			ft_putstr_fd("\033[0m", 1);
			ft_putstr_fd("\nbuf contient : \033[0;36m", 1);
			ft_putstr_fd(buf, 1);
			ft_putstr_fd("\033[0m", 1);
			*line = ft_strjoin(*line, buf); 
			ft_memcpy(buf, newline, BUFFER_SIZE);
/*			ft_memcpy(buf, newline, ft_strlen(buf));*/
			ft_putstr_fd("Pour voir ce que donne la newline 2: \033[1;31m", 1);
			ft_putstr_fd(newline, 1);
			ft_putstr_fd("\033[0m", 1);
			ft_putstr_fd("\nbuf contient : \033[0;36m", 1);
			ft_putstr_fd(buf, 1);
			ft_putstr_fd("\033[0m", 1);

		/*	free(newline);*/
		}
		else
		{
			*line = ft_strjoin(*line, buf);
		}
	}
	ft_putstr_fd("\nbuf final contient : \033[0;36m", 1);
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\033[0m", 1);ft_putstr_fd("\nDans la line, on a : \033[1;32m", 1);
	ft_putstr_fd(*line, 1);
	ft_putstr_fd("\033[0m", 1);
	

	if (ret > 0 /*|| newline*/)
		ret = 1;
	printf("\nret : %d\n", ret);
	return (ret);
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
/*	while (i++ <= 4)*/
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
