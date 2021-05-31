
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
/* Version gnl sv */
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
