/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:24 by root              #+#    #+#             */
/*   Updated: 2024/10/26 21:35:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void flood_fill(char **map_cpy, int x, int y, int *col, int *exit_rchd)
{
	if (map_cpy[y][x] == '1' || map_cpy[y][x] == 'F' || map_cpy[y][x] == 'M')
		return;// Ignorer murs, mobs et cases déjà visitées
	if (map_cpy[y][x] == 'C')
		(*col)--;
	if (map_cpy[y][x] == 'E')
		*exit_rchd = 1;
	map_cpy[y][x] = 'F';  // Marquer la case comme visitée
	flood_fill(map_cpy, x + 1, y, col, exit_rchd);
	flood_fill(map_cpy, x - 1, y, col, exit_rchd);
	flood_fill(map_cpy, x, y + 1, col, exit_rchd);
	flood_fill(map_cpy, x, y - 1, col, exit_rchd);
}

int	is_map_solvable(t_game *g)
{
	int		height;
	int		cols;
	int		ext_rcd;
	int		i;
	char	**map_cpy;

	height = g->map_height;
	i = 0;
	map_cpy = malloc(sizeof(char *) * height);
	while (i < height)
	{
		map_cpy[i] = ft_strdup(g->map[i]);// Créer une copie de chaque ligne
		i++;
	}
	cols = g->c_count;
	ext_rcd = 0;
	flood_fill(map_cpy, g->player_x / SIZE, g->player_y / SIZE, &cols, &ext_rcd);
	i = 0;
	while (i < height)
	{
		free(map_cpy[i]);
		i++;
	}
	free(map_cpy);
	return (cols == 0 && ext_rcd);
}
