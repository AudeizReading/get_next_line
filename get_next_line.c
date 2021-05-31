/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:54:45 by alellouc          #+#    #+#             */
/*   Updated: 2021/05/31 14:20:37 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
/* Uniquement pour le debugage */
#include <stdio.h>
/* Fin debugage */


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
	/*int			ret;
	static char		buf[BUFFER_SIZE + 1];
	char	*newline;
	char		*tmp;
	char		*test;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
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
	return (ret);*/
	int			ret;
	static char	*buf;
	char		*newline;
	char		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!buf)
		buf = ft_calloc(sizeof(*buf), BUFFER_SIZE);
	newline = ft_strdup("");
	ret = 1;
	while (!ft_strchr(buf, '\n') && ret > 0)
	{
		printf("buf avant travail dessus: \033[1;31m%s\033[0m\n", buf);
		printf("newline avant travail dessus: \033[1;31m%s\033[0m\n", newline);
		newline = ft_strjoin(newline, buf);
	/*	if (buf)
			free(buf);*/
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (-1);
		buf[ret] = 0;
		printf("buf apres travail dessus: \033[31m%s\033[0m\n", buf);
		printf("newline apres travail dessus: \033[31m%s\033[0m\n", newline);
		printf("\033[31m----------------------------------------------------------\033[0m\n");
	}
	printf("buf sortie boucle while: \033[33m%s\033[0m\n", buf);
	printf("newline sortie boucle while: \033[33m%s\033[0m\n", newline);
	printf("\033[33m----------------------------------------------------------\033[0m\n");
	if (ft_strchr(buf, '\n'))
	{
		tmp = ft_calloc(sizeof(*tmp), ret);
		buf = ft_memccpy(tmp, buf, '\n', ret);
		newline = ft_strjoin(newline, tmp);
	/*	free(tmp);*/
	}
	else
	{
	/*	tmp = ft_strdup(buf);*/
	/*	newline = ft_strjoin(newline, tmp); */
		printf("\033[35mDon't know what about it, just for the non segfault\033[0m\n");
	}
	*line = ft_strdup(newline);
	free(newline);
	if (ret == 0)
	{
	/*	if (buf)
			free(buf);*/
		return (0);
	}
	else
		return (1);
}
