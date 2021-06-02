/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:25:09 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/02 12:56:28 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#include <stdio.h>
#include <fcntl.h>

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

int	main(int argc, char **argv)
{
	char	*line;
	size_t	fd1;
	size_t	fd2;
	size_t	fd3;
	int		gnl;

	if (argc == 4)
	{
		fd1 = open(argv[1], O_RDONLY);
		fd2 = open(argv[2], O_RDONLY);
		fd3 = open(argv[3], O_RDONLY);
	}
	else
	{
		ft_putstr_fd("Il faut indiquer 3 noms de fichiers en paramètres, sans quoi le programme bonus ne se lancera pas\n", 1);
		return (1);
	}
/*	while ((gnl = get_next_line(fd[i++], &line)) > 0)
	{
		ft_putstr_fd(line, 1);
		ft_putstr_fd("\n", 1);
		free(line);
		if (i == 2)
			i = 0;
	}*/
	gnl = get_next_line(fd1, &line);
	if (gnl == -1)
		ft_putstr_fd("Votre gnl a rencontré un souci\n", 1);
	ft_putstr_fd("Premiere ligne du fichier ", 1);
	ft_putstr_fd(argv[1], 1);
	ft_putstr_fd("\n\033[32m", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\033[0m\n", 1);
	free(line);

	gnl = get_next_line(fd2, &line);
	if (gnl == -1)
		ft_putstr_fd("Votre gnl a rencontré un souci\n", 1);
	ft_putstr_fd("Premiere ligne du fichier ", 1);
	ft_putstr_fd(argv[2], 1);
	ft_putstr_fd("\n\033[33m", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\033[0m\n", 1);
	free(line);

	gnl = get_next_line(fd3, &line);
	if (gnl == -1)
		ft_putstr_fd("Votre gnl a rencontré un souci\n", 1);
	ft_putstr_fd("Premiere ligne du fichier ", 1);
	ft_putstr_fd(argv[3], 1);
	ft_putstr_fd("\n\033[33m", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\033[0m\n", 1);
	free(line);

	gnl = get_next_line(fd1, &line);
	if (gnl == -1)
		ft_putstr_fd("Votre gnl a rencontré un souci\n", 1);
	ft_putstr_fd("Deuxieme ligne du fichier ", 1);
	ft_putstr_fd(argv[1], 1);
	ft_putstr_fd("\n\033[32m", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\033[0m\n", 1);
	free(line);

	gnl = get_next_line(fd2, &line);
	if (gnl == -1)
		ft_putstr_fd("Votre gnl a rencontré un souci\n", 1);
	ft_putstr_fd("Deuxieme ligne du fichier ", 1);
	ft_putstr_fd(argv[2], 1);
	ft_putstr_fd("\n\033[33m", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\033[0m\n", 1);
	free(line);

	gnl = get_next_line(fd3, &line);
	if (gnl == -1)
		ft_putstr_fd("Votre gnl a rencontré un souci\n", 1);
	ft_putstr_fd("Deuxieme ligne du fichier ", 1);
	ft_putstr_fd(argv[3], 1);
	ft_putstr_fd("\n\033[33m", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\033[0m\n", 1);
	free(line);

	gnl = get_next_line(fd1, &line);
	if (gnl == -1)
		ft_putstr_fd("Votre gnl a rencontré un souci\n", 1);
	ft_putstr_fd("Troisieme ligne du fichier ", 1);
	ft_putstr_fd(argv[1], 1);
	ft_putstr_fd("\n\033[32m", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\033[0m\n", 1);
	free(line);

	gnl = get_next_line(fd2, &line);
	if (gnl == -1)
		ft_putstr_fd("Votre gnl a rencontré un souci\n", 1);
	ft_putstr_fd("Troisieme ligne du fichier ", 1);
	ft_putstr_fd(argv[2], 1);
	ft_putstr_fd("\n\033[33m", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\033[0m\n", 1);
	free(line);

	gnl = get_next_line(fd3, &line);
	if (gnl == -1)
		ft_putstr_fd("Votre gnl a rencontré un souci\n", 1);
	ft_putstr_fd("Premiere ligne du fichier ", 1);
	ft_putstr_fd(argv[3], 1);
	ft_putstr_fd("\n\033[33m", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\033[0m\n", 1);
	free(line);

/*	if (gnl == -1)
		ft_putstr_fd("Votre gnl a rencontré un souci\n", 1);
	if (line)
	{
		ft_putstr_fd(line, 1);
		ft_putstr_fd("\n", 1);
		free(line);
	}*/
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

