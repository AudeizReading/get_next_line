/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:54:45 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/03 15:59:58 by alellouc         ###   ########.fr       */
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

char	*ft_parse_buf(size_t bytes, char *buf, char **newline)
{
	char	*end_line;
	/*char	*next_line;*/
	size_t	end_len;
	size_t	begin_len;

	/*next_line = ft_strchr(*buf, '\n');*/ /* voir si on malloc ca ou si on le supprime */
	/*end_len = next_line - *buf;*/
	end_len = ft_strchr(buf, '\n') - buf;
	begin_len = bytes - end_len + 1;
	end_line = ft_calloc(sizeof(*end_line), end_len);
	if (!end_line)
		return (NULL);
/*	printf("\tbuffer avant travail dessus  : \033[33m%s\033[0m\n", buf);*/
	ft_memccpy(buf, ft_memccpy(end_line, buf, '\n', end_len), '\0', begin_len);
/*	ft_memccpy(buf, ft_memccpy(end_line, buf, '\n', end_len), '\0', bytes -
**	ft_strlen(end_line));*/
/*	printf("\tbegin_len : \033[36m%ld\033[0m\n", begin_len);
	printf("\tbytes - ft_strlen(end_line) : \033[36m%ld\033[0m\n", bytes - ft_strlen(end_line));
	printf("\tend_line apres travail dessus : \033[35m%s\033[0m\n", end_line);
	printf("\tbuffer apres travail dessus : \033[35m%s\033[0m\n", buf);*/
	/* free(next_line); */
	*newline = ft_strjoin(*newline, end_line);
/*	printf("\tnewline apres travail dessus : \033[35m%s\033[0m\n", *newline);*/
	if (!*newline)
		return (NULL);
	free(end_line);
	return (*newline);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	static char	buf[BUFFER_SIZE + 1];
	char		*newline;

	if (read(fd, buf, 0) < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	newline = ft_strdup("");
	ret = ft_strlen(buf) + 1;
	while (!ft_strchr(buf, '\n') && ret > 0)
	{
		newline = ft_strjoin(newline, buf);
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1 || !newline)
			return (-1);
		buf[ret] = 0;
	}
	if (ft_strchr(buf, '\n'))
		newline = ft_parse_buf(ret, buf, &newline);
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
