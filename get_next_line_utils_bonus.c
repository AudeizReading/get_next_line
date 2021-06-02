/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:21:08 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/02 12:21:45 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t				len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}


void	*ft_calloc(size_t count, size_t size)
{
	unsigned char		*buffer;
	size_t				len;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	len = size * count;
	buffer = malloc(len);
	if (!buffer)
		return (NULL);
	while (len--)
		buffer[len] = 0;
	return ((void *)buffer);
}

char	*ft_strdup(const char *s1)
{
	size_t				len_s1;
	char				*dest;

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

char	*ft_strchr(const char *s, int c)
{
	char				*p_s;
	char				c_c;

	p_s = (char *)s;
	c_c = (char)c;
	while (*p_s)
		if (*p_s++ == c_c)
			return (p_s);
	return (NULL);
}