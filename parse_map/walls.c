/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 23:29:40 by root              #+#    #+#             */
/*   Updated: 2024/10/26 21:38:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	upper_walls(t_game *g, int fd)
{
	int	i;

	i = 0;
	while (g->map[0][i])
	{
		if (g->map[0][i] != '1' && g->map[0][i] != '\n')
		{
			perror("Veuillez mettre des murs tout autour de la map!(dessus)");
			i = 0;
			while (g->map[i] != NULL)
			{
				free(g->map[i]);
				i++;
			}
			free(g->map);
			close(fd);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	bottom_wall(t_game *g, int fd, int idx)
{
	int	i;

	i = 0;
	while (g->map[idx][i])
	{
		if (g->map[idx][i] != '1' && g->map[idx][i] != '\n')
		{
			perror("Veuillez mettre des murs tout autour de la map!(dessous)");
			i = 0;
			while (g->map[i] != NULL)
			{
				free(g->map[i]);
				i++;
			}
			free(g->map);
			close(fd);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	check_walls(t_game *g, int fd)
{
	int	i;
	int	y;

	i = 0;
	y = 1;
	upper_walls(g, fd);
	while (g->map[y + 1] != NULL)
	{
		if (g->map[y][0] != '1' || g->map[y][ft_strlen(g->map[y]) - 2] != '1')
		{
			perror("Veuillez mettre des murs tout autour de la map!(cotés)");
			i = 0;
			while (g->map[i] != NULL)
			{
				free(g->map[i]);
				i++;
			}
			free(g->map);
			exit(EXIT_FAILURE);
		}
		y++;
	}
	bottom_wall(g, fd, y);
}
