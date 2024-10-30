/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:37:35 by root              #+#    #+#             */
/*   Updated: 2024/10/30 17:13:08 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	display_move_count(t_game *g)
{
	char	*str;
	char	*s;

	str = ft_itoa(g->moves);
	s = ft_strjoin("Mouvement : ", str);
	mlx_put_image_to_window(g->mlx, g->win, g->wall_img, 0, 0);
	mlx_put_image_to_window(g->mlx, g->win, g->wall_img, 64, 0);
	mlx_string_put(g->mlx, g->win, 10, 10, 0xFFFFFF, s);
	free(str);
	free(s);
}

static void	check_action2(int new_x, int new_y, t_game *g)
{
	if (g->map[new_y / SIZE][new_x / SIZE] == 'M')
		game_over(g);
	if (g->map[new_y / SIZE][new_x / SIZE] == 'C')
	{
		mlx_put_image_to_window(g->mlx, g->win,
			g->floor_img, g->player_x, g->player_y);
		g->player_x = new_x;
		g->player_y = new_y;
		mlx_put_image_to_window(g->mlx, g->win,
			g->player_img, g->player_x, g->player_y);
		g->map[new_y / SIZE][new_x / SIZE] = '0';
		g->colected_count++;
		ft_printf("collectible restant: %d\n", g->c_count - g->colected_count);
	}
	if (g->map[new_y / SIZE][new_x / SIZE] == 'E')
	{
		if (g->c_count == g->colected_count)
			game_win(g);
	}
}

static void	check_action(int new_x, int new_y, t_game *g)
{
	if (g->map[new_y / SIZE][new_x / SIZE] == '0'
		|| g->map[new_y / SIZE][new_x / SIZE] == 'P' )
	{
		mlx_put_image_to_window(g->mlx, g->win,
			g->floor_img, g->player_x, g->player_y);
		g->player_x = new_x;
		g->player_y = new_y;
		g->moves++;
		display_move_count(g);
		ft_printf("Moves: %d\n", g->moves);
		mlx_put_image_to_window(g->mlx, g->win,
			g->player_img, g->player_x, g->player_y);
	}
	else
		check_action2(new_x, new_y, g);
}

static void	check_if_walls(int new_x, int new_y, t_game *g)
{
	if (new_x >= 0 && new_x < g->map_width * SIZE
		&& new_y >= 0 && new_y < g->map_height * SIZE)
	{
		if (g->map[new_y / SIZE][new_x / SIZE] != '1')
			check_action(new_x, new_y, g);
	}
}

int	key_hook(int keycode, t_game *g)
{
	int	new_x;
	int	new_y;

	new_x = g->player_x;
	new_y = g->player_y;
	if (keycode == 65307)
	{
		free_game_resources(g);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 65361)
		new_x -= SIZE;
	else if (keycode == 65363)
		new_x += SIZE;
	else if (keycode == 65362)
		new_y -= SIZE;
	else if (keycode == 65364)
		new_y += SIZE;
	if (keycode == 65361 || keycode == 65362 || keycode == 65363
		|| keycode == 65364)
		check_if_walls(new_x, new_y, g);
	return (0);
}
