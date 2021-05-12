/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:54:45 by alellouc          #+#    #+#             */
/*   Updated: 2021/05/12 10:42:40 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	len_s1;
	char	*dest;

	len_s1 = ft_strlen(s1);
	dest = (char *)ft_calloc((len_s1 + 1), sizeof(*dest));
	if (!dest)
	{
		errno = ENOMEM;
		return ((char *)0);
	}
	ft_memcpy(dest, s1, len_s1);
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
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

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*buffer;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	buffer = malloc(size * count);
	if (buffer == NULL)
		return (NULL);
	ft_bzero(buffer, size * count);
	return ((void *)buffer);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p_b;
	unsigned char	c_c;

	p_b = b;
	c_c = c;
	while (len--)
		*p_b++ = c_c;
	return (b);
}

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

int	get_next_line(int fd, char **line)
{
	int	ret;
	static char buf[BUFFER_SIZE + 1];

	ret = read(fd, buf, BUFFER_SIZE);
	*line = ft_strdup(buf);
	if (ret > 0)
		ret = 1;
	return (ret);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	char	*line;

	get_next_line(0, &line);
	ft_putstr_fd(line, 0);
	return (0);
}
