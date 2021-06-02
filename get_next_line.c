/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:54:45 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/02 15:44:38 by alellouc         ###   ########.fr       */
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
	int			ret;
	static char	buf[BUFFER_SIZE + 1];
	char		*newline;
	char		*tmp;

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
	{
		/*tmp = ft_calloc(sizeof(*tmp), ret);*/
		tmp = ft_calloc(sizeof(*tmp), ft_strchr(buf, '\n') - buf);
		if (!tmp)
		{
			free(newline);
			return (-1);
		}
		ft_memccpy(buf, ft_memccpy(tmp, buf, '\n', ft_strchr(buf, '\n') - buf), '\0', ret - ft_strlen(ft_strchr(buf, '\n')));
		newline = ft_strjoin(newline, tmp);
		free(tmp);
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
