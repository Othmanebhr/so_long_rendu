/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:24 by root              #+#    #+#             */
/*   Updated: 2024/10/30 13:50:30 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	flood_fill(char **map_cpy, int x, int y, int info[2])
{
	if (map_cpy[y][x] == 'E')
		info[1] = 1;
	if (map_cpy[y][x] == '1' || map_cpy[y][x] == 'F' || map_cpy[y][x] == 'M'
			|| map_cpy[y][x] == 'E')
		return ;
	if (map_cpy[y][x] == 'C')
		info[0]--;
	map_cpy[y][x] = 'F';
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
	int		info[2];

	height = g->map_height;
	i = 0;
	map_cpy = malloc(sizeof(char *) * height);
	while (i < height)
	{
		map_cpy[i] = ft_strdup(g->map[i]);
		i++;
	}
	info[0] = g->c_count;
	info[1] = 0;
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