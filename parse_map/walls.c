/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 23:29:40 by root              #+#    #+#             */
/*   Updated: 2024/10/14 02:50:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	upper_walls(t_game	*game, int fd)
{
	int	i;

	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != '1' && game->map[0][i] != '\n')
		{
			perror("Veuillez mettre des murs tout autour de la map! (murs du dessus)");
			i = 0;
			while(game->map[i] != NULL)
			{
				free(game->map[i]);
				i++;
			}
			free(game->map);
			close(fd);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	bottom_wall(t_game	*game, int fd, int idx)
{
	int	i;

	i = 0;
	while (game->map[idx][i])
	{
		if (game->map[idx][i] != '1' && game->map[idx][i] != '\n')
		{
			perror("Veuillez mettre des murs tout autour de la map! (murs du dessous)");
			i = 0;
			while(game->map[i] != NULL)
			{
				free(game->map[i]);
				i++;
			}
			free(game->map);
			close(fd);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	check_walls(t_game	*game, int fd)
{
	int	i;
	int	y;

	i = 0;
	y = 1;
	upper_walls(game, fd);
	while (game->map[y + 1] != NULL)
	{
		if (game->map[y][0] != '1' || game->map[y][ft_strlen(game->map[y]) - 2] != '1')
		{
			perror("Veuillez mettre des murs tout autour de la map! (murs de cotés)");
			i = 0;
			while(game->map[i] != NULL)
			{
				free(game->map[i]);
				i++;
			}
			free(game->map);
			exit(EXIT_FAILURE);
		}
		y++;
	}
	bottom_wall(game, fd, y);
}