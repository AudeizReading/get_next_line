/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 10:31:13 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/02 13:10:33 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"
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
	int			ret;
	static char	buf[255][BUFFER_SIZE + 1];
	char		*newline;
	char		*tmp;

	if (read(fd, buf[fd], 0) < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	newline = ft_strdup("");
	ret = ft_strlen(buf[fd]) + 1;
	while (!ft_strchr(buf[fd], '\n') && ret > 0)
	{
	/*	printf("buf avant travail dessus: \033[1;31m%s\033[0m\n", buf);
		printf("newline avant travail dessus: \033[1;31m%s\033[0m\n", newline);*/
		newline = ft_strjoin(newline, buf[fd]);
		ret = read(fd, buf[fd], BUFFER_SIZE);
		if (ret == -1 || !newline)
			return (-1);
		buf[fd][ret] = 0;
/*		printf("buf apres travail dessus: \033[31m%s\033[0m\n", buf);
		printf("newline apres travail dessus: \033[31m%s\033[0m\n", newline);
		printf("\033[31m----------------------------------------------------------\033[0m\n");*/
	}
/*	printf("buf sortie boucle while: \033[33m%s\033[0m\n", buf);
	printf("newline sortie boucle while: \033[33m%s\033[0m\n", newline);
	printf("\033[33m----------------------------------------------------------\033[0m\n");*/
	if (ft_strchr(buf[fd], '\n'))
	{
		tmp = ft_calloc(sizeof(*tmp), ret);
		if (!tmp)
		{
			free(newline);
			return (-1);
		}
		ft_memccpy(buf[fd], ft_memccpy(tmp, buf[fd], '\n', ret), '\0', BUFFER_SIZE);
	/*	printf("buf, avant affectation: \033[36m%s\033[0m\n", buf);
		printf("tmp, apres affectation: \033[36m%s\033[0m\n", tmp);*/
		newline = ft_strjoin(newline, tmp);
		free(tmp);
	/*	printf("newline, apres affectation: \033[36m%s\033[0m\n", newline);
		printf("buf, apres affectation: \033[36m%s\033[0m\n", buf);
		printf("\033[36m----------------------------------------------------------\033[0m\n");*/
	}
	*line = ft_strdup(newline);
	if (!*line)
	{
		free(newline);
		return (-1);
	}
	free(newline);
	if (ret == 0)
		return (0);
	return (1);
}
