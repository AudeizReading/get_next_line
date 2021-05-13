/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:45:29 by alellouc          #+#    #+#             */
/*   Updated: 2021/05/13 11:41:26 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/errno.h>

int		get_next_line(int fd, char **line);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
#endif
