/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:24 by root              #+#    #+#             */
/*   Updated: 2024/10/30 01:53:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// static void	flood_fill(char **map_cpy, int x, int y, int info[2])
// {
// 	if (map_cpy[y][x] == '1' || map_cpy[y][x] == 'F' || map_cpy[y][x] == 'M')
// 		return ; // Ignorer murs, mobs et cases déjà visitées
// 	if (map_cpy[y][x] == 'C')
// 		info[0]--;// info[0] représente col
// 	if (map_cpy[y][x] == 'E')
// 		info[1] = 1;// info[1] représente exit_rchd
// 	map_cpy[y][x] = 'F';// Marquer la case comme visitée
// 	flood_fill(map_cpy, x + 1, y, info);
// 	flood_fill(map_cpy, x - 1, y, info);
// 	flood_fill(map_cpy, x, y + 1, info);
// 	flood_fill(map_cpy, x, y - 1, info);
// }

static void	flood_fill(char **map_cpy, int x, int y, int info[2])
{
	if (map_cpy[y][x] == 'E')
		info[1] = 1;
	if (map_cpy[y][x] == '1' || map_cpy[y][x] == 'F' || map_cpy[y][x] == 'M'
			|| map_cpy[y][x] == 'E')
		return ;  // Ignorer murs, mobs et cases déjà visitées
	if (map_cpy[y][x] == 'C')
		info[0]--;
	map_cpy[y][x] = 'F';  // Marquer la case comme visitée
	flood_fill(map_cpy, x + 1, y, info);
	flood_fill(map_cpy, x - 1, y, info);
	flood_fill(map_cpy, x, y + 1, info);
	flood_fill(map_cpy, x, y - 1, info);
}

int	is_map_solvable(t_game *g)
{
	int		height;
	int		i;
	char	**map_cpy;
	int		info[2]; // Tableau pour stocker col et exit_rchd
	height = g->map_height;
	i = 0;
	map_cpy = malloc(sizeof(char *) * height);
	while (i < height)
	{
		map_cpy[i] = ft_strdup(g->map[i]); // Créer une copie de chaque ligne
		i++;
	}
	info[0] = g->c_count; // col
	info[1] = 0; // exit_rchd
	flood_fill(map_cpy, g->player_x / SIZE, g->player_y / SIZE, info);
	i = 0;
	while (i < height)
	{
		free(map_cpy[i]);
		i++;
	}
	free(map_cpy);
	return (info[0] == 0 && info[1]);
}

//info[0} représente les collectible;
//info[1] représente la sortie