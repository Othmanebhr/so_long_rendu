/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:00:09 by root              #+#    #+#             */
/*   Updated: 2024/10/25 13:49:07 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	load_img2(t_game *game, int *height, int *width)
{
	game->player_img = mlx_xpm_file_to_image(game->mlx, "sprites/player.xpm", width, height);
	if (!game->player_img)
	{
		free_game_resources(game);
		handle_error("Failed to load player image");
	}
	game->collectible_img = mlx_xpm_file_to_image(game->mlx, "sprites/tresor.xpm", width, height);
	if (!game->collectible_img)
	{
		free_game_resources(game);
		handle_error("Failed to load collectible image");
	}
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "sprites/crown.xpm", width, height);
	if (!game->exit_img)
	{
		free_game_resources(game);
		handle_error("Failed to load exit image");
	}
}

void load_img(t_game *game)
{
	int	width;
	int	height;

	game->wall_img = mlx_xpm_file_to_image(game->mlx, "sprites/walls.xpm", &width, &height);
	if (!game->wall_img)
	{
		free_game_resources(game);
		handle_error("Failed to load wall image");
	}
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "sprites/Sol.xpm", &width, &height);
	if (!game->floor_img)
	{
		free_game_resources(game);
		handle_error("Failed to load floor image");
	}
	game->mob_img = mlx_xpm_file_to_image(game->mlx, "sprites/mob.xpm", &width, &height);
	if (!game->mob_img)
	{
		free_game_resources(game);
		handle_error("Failed to load mob image");
	}
	load_img2(game, &width, &height);
}


void	render_map(t_game *game, char **map)
{
	int x, y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if (map[y][x] == '1' && game->wall_img)
				mlx_put_image_to_window(game->mlx, game->win, game->wall_img, x * SIZE, y * SIZE);
			else if (map[y][x] == '0' && game->floor_img)
				mlx_put_image_to_window(game->mlx, game->win, game->floor_img, x * SIZE, y * SIZE);
			else if (map[y][x] == 'P' && game->player_img)
				mlx_put_image_to_window(game->mlx, game->win, game->player_img, x * SIZE, y * SIZE);
			else if (map[y][x] == 'E' && game->exit_img)
				mlx_put_image_to_window(game->mlx, game->win, game->exit_img, x * SIZE, y * SIZE);
			else if (map[y][x] == 'C' && game->collectible_img)
				mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, x * SIZE, y * SIZE);
			else if (map[y][x] == 'M' && game->mob_img)
				mlx_put_image_to_window(game->mlx, game->win, game->mob_img, x * SIZE, y * SIZE);
			x++;
		}
		y++;
	}
}
