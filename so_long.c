/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:03:18 by root              #+#    #+#             */
/*   Updated: 2024/10/30 17:11:47 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".ber") != 0)
		handle_error("The file must have a .ber extension");
}

static void	init_s(t_game *g)
{
	g->moves = 0;
	g->colected_count = 0;
	g->collectible_img = NULL;
	g->mob_img = NULL;
	g->exit_img = NULL;
	g->wall_img = NULL;
	g->floor_img = NULL;
	g->player_img = NULL;
	g->mobs = NULL;
	g->col = NULL;
}

static int	close_window(t_game *g)
{
	free_game_resources(g);
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	g;

	if (ac > 2)
		handle_error("Too much arguments");
	if (ac < 2)
		handle_error("Too few arguments");
	check_file_extension(av[1]);
	open_and_fill_map(&g, av);
	init_s(&g);
	g.mlx = mlx_init();
	if (!g.mlx)
	{
		free_game_resources(&g);
		handle_error("Failed to initialize mlx");
	}
	g.win = mlx_new_window(g.mlx, g.map_width * SIZE,
			g.map_height * SIZE, "so_long");
	load_img(&g);
	check_every_position(&g);
	render_map(&g, g.map);
	mlx_key_hook(g.win, key_hook, &g);
	mlx_hook(g.win, 17, 0, close_window, &g);
	mlx_loop(g.mlx);
	return (0);
}
