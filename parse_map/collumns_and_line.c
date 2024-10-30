/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collumns_and_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:02:32 by root              #+#    #+#             */
/*   Updated: 2024/10/27 15:40:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	free_all_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static void	count_collumns2(int count, int fd)
{
	int		count_check;
	char	*collumns;

	count_check = 0;
	collumns = get_next_line(fd);
	while (collumns != NULL)
	{
		count_check = ft_strlen(collumns);
		if (collumns[ft_strlen(collumns) - 1] == '\n')
			count_check -= 1;
		if (count_check != count)
		{
			free(collumns);
			free_all_lines(fd);
			handle_error_close("Vous n'avez pas le même nombre de colonne", fd);
		}
		free(collumns);
		collumns = get_next_line(fd);
	}
}

int	count_collumns(char *file)
{
	int		count;
	int		fd;
	char	*collumns;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error("L'ouverture de la map a échoué");
	collumns = get_next_line(fd);
	if (!collumns)
		handle_error_close("Erreur lors de la lecture de la 1ère ligne", fd);
	if (collumns[ft_strlen(collumns) - 1] == '\n')
		count = ft_strlen(collumns) - 1;
	else
		count = ft_strlen(collumns);
	free(collumns);
	count_collumns2(count, fd);
	close(fd);
	return (count);
}

int	count_line(char *file)
{
	int		count;
	int		fd;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("L'ouverture de la map a échoué");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

// int	count_line(char	*file)
// {
// 	int		count;
// 	int		fd;
// 	char	*line;

// 	count = 0;
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("L'ouverture de la map a échoué");
// 		exit(EXIT_FAILURE);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		count++;
// 		free(line);
// 	}
// 	close(fd);
// 	return (count);
// }
