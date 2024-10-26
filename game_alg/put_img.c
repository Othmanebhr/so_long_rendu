/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:00:09 by root              #+#    #+#             */
/*   Updated: 2024/10/26 21:30:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	load_img2(t_game *g, int *height, int *width)
{
	g->player_img = mlx_xpm_file_to_image(g->mlx,
			"sprites/player.xpm", width, height);
	if (!g->player_img)
	{
		free_game_resources(g);
		handle_error("Failed to load player image");
	}
	g->collectible_img = mlx_xpm_file_to_image(g->mlx,
			"sprites/tresor.xpm", width, height);
	if (!g->collectible_img)
	{
		free_game_resources(g);
		handle_error("Failed to load collectible image");
	}
	g->exit_img = mlx_xpm_file_to_image(g->mlx,
			"sprites/crown.xpm", width, height);
	if (!g->exit_img)
	{
		free_game_resources(g);
		handle_error("Failed to load exit image");
	}
}

void	load_img(t_game *g)
{
	int	width;
	int	height;

	g->wall_img = mlx_xpm_file_to_image(g->mlx,
			"sprites/walls.xpm", &width, &height);
	if (!g->wall_img)
	{
		free_game_resources(g);
		handle_error("Failed to load wall image");
	}
	g->floor_img = mlx_xpm_file_to_image(g->mlx,
			"sprites/Sol.xpm", &width, &height);
	if (!g->floor_img)
	{
		free_game_resources(g);
		handle_error("Failed to load floor image");
	}
	g->mob_img = mlx_xpm_file_to_image(g->mlx,
			"sprites/mob.xpm", &width, &height);
	if (!g->mob_img)
	{
		free_game_resources(g);
		handle_error("Failed to load mob image");
	}
	load_img2(g, &width, &height);
}

static void	put_image_to_window(t_game *g, char **map, int x, int y)
{
	if (map[y][x] == '1' && g->wall_img)
		mlx_put_image_to_window(g->mlx, g->win,
			g->wall_img, x * SIZE, y * SIZE);
	else if (map[y][x] == '0' && g->floor_img)
		mlx_put_image_to_window(g->mlx, g->win,
			g->floor_img, x * SIZE, y * SIZE);
	else if (map[y][x] == 'P' && g->player_img)
		mlx_put_image_to_window(g->mlx, g->win,
			g->player_img, x * SIZE, y * SIZE);
	else if (map[y][x] == 'E' && g->exit_img)
		mlx_put_image_to_window(g->mlx, g->win,
			g->exit_img, x * SIZE, y * SIZE);
	else if (map[y][x] == 'C' && g->collectible_img)
		mlx_put_image_to_window(g->mlx, g->win,
			g->collectible_img, x * SIZE, y * SIZE);
	else if (map[y][x] == 'M' && g->mob_img)
		mlx_put_image_to_window(g->mlx, g->win,
			g->mob_img, x * SIZE, y * SIZE);
}

void	render_map(t_game *g, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			put_image_to_window(g, map, x, y);
			x++;
		}
		y++;
	}
}
