/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collumns_and_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:02:32 by root              #+#    #+#             */
/*   Updated: 2024/10/19 00:53:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"


static void count_collumns2(int count, int fd)
{
	int		count_check;
	char	*collumns;

	count_check = 0;
	while ((collumns = get_next_line(fd)) != NULL)
	{
		count_check = ft_strlen(collumns);
		
		// Si la ligne a un '\n' à la fin, on ignore ce '\n'
		if (collumns[ft_strlen(collumns) - 1] == '\n')
			count_check -= 1;
		
		// Si le nombre de colonnes ne correspond pas
		if (count_check != count)
		{
			free(collumns);
			handle_error_close("Vous n'avez pas le même nombre de colonne", fd);
		}
		free(collumns);
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
		handle_error_close("Erreur lors de la lecture de la première ligne", fd);
	if (collumns[ft_strlen(collumns) - 1] == '\n')
		count = ft_strlen(collumns) - 1;
	else
		count = ft_strlen(collumns);
	free(collumns);
	count_collumns2(count, fd);
	close(fd);
	return (count);
}

int	count_line(char	*file)
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
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}
