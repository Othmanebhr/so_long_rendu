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

void flood_fill(char **map_copy, int x, int y, int *collectibles, int *exit_reached)
{
    if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
        return;

    if (map_copy[y][x] == 'C')
        (*collectibles)--;

    if (map_copy[y][x] == 'E')
        *exit_reached = 1;

    map_copy[y][x] = 'F';

    flood_fill(map_copy, x + 1, y, collectibles, exit_reached);
    flood_fill(map_copy, x - 1, y, collectibles, exit_reached);
    flood_fill(map_copy, x, y + 1, collectibles, exit_reached);
    flood_fill(map_copy, x, y - 1, collectibles, exit_reached);
}


int is_map_solvable(t_game *game)
{
	int height = game->map_height;
	int width = game->map_width;
	char **map_copy = malloc(sizeof(char *) * height);
	for (int i = 0; i < height; i++)
	{
		map_copy[i] = strdup(game->map[i]);  // Créer une copie de chaque ligne
	}

	int collectibles = game->c_count;
	int exit_reached = 0;

	flood_fill(map_copy, game->player_x / SIZE, game->player_y / SIZE, &collectibles, &exit_reached);

	// Libérer la mémoire de la copie
	for (int i = 0; i < height; i++)
	{
		free(map_copy[i]);
	}
	free(map_copy);

	// Vérification si tous les collectables ont été récupérés et si la sortie est atteignable
	return (collectibles == 0 && exit_reached);
}
