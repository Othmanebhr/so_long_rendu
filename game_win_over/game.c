/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:30:59 by root              #+#    #+#             */
/*   Updated: 2024/10/26 19:42:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	free_game_resources3(t_game *game)
{
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->collectible_img)
		mlx_destroy_image(game->mlx, game->collectible_img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}

static void	free_game_resources2(t_game *game)
{
	int	i;

	i = 0;
	if (game->mobs)
	{
		while (i < game->mob_count)
		{
			free(game->mobs[i]);
			i++;
		}
		free(game->mobs);
	}
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->mob_img)
		mlx_destroy_image(game->mlx, game->mob_img);
	free_game_resources3(game);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	free_game_resources(t_game *game)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	i = 0;
	if (game->col)
	{
		while (i < game->c_count)
		{
			free(game->col[i]);
			i++;
		}
		free(game->col);
	}
	free_game_resources2(game);
}

void	game_over(t_game *game)
{
	ft_printf("You lost!\n");
	free_game_resources(game);
	exit(EXIT_SUCCESS);
}

void	game_win(t_game *game)
{
	ft_printf("Congrats you won!\n");
	free_game_resources(game);
	exit(EXIT_SUCCESS);
}
