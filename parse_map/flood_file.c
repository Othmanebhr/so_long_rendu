/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:24 by root              #+#    #+#             */
/*   Updated: 2024/10/24 16:25:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void flood_fill(char **map_copy, int x, int y, int *col, int *exit_rchd)
{
    if (map_copy[y][x] == '1' || map_copy[y][x] == 'F' || map_copy[y][x] == 'M')
        return;  // Ignorer murs, mobs et cases déjà visitées
    if (map_copy[y][x] == 'C')
        (*col)--;
    if (map_copy[y][x] == 'E')
        *exit_rchd = 1;

    map_copy[y][x] = 'F';  // Marquer la case comme visitée

    flood_fill(map_copy, x + 1, y, col, exit_rchd);
    flood_fill(map_copy, x - 1, y, col, exit_rchd);
    flood_fill(map_copy, x, y + 1, col, exit_rchd);
    flood_fill(map_copy, x, y - 1, col, exit_rchd);
}


int is_map_solvable(t_game *game)
{
	int height;
	char **map_copy;
	int collectibles;
	int exit_reached;
	int i;

	height = game->map_height;
	i = 0;
	map_copy = malloc(sizeof(char *) * height);
	while(i < height)
	{
		map_copy[i] = ft_strdup(game->map[i]);  // Créer une copie de chaque ligne
		i++;
	}
	collectibles = game->c_count;
	exit_reached = 0;
	flood_fill(map_copy, game->player_x / SIZE, game->player_y / SIZE, &collectibles, &exit_reached);
	i = 0;
	while (i < height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	return (collectibles == 0 && exit_reached);
}
