/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:03:18 by root              #+#    #+#             */
/*   Updated: 2024/10/26 21:39:20 by root             ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_game	g;

	if (ac > 2)
		handle_error("Too much arguments");
	if (ac < 2)
		handle_error("Too few arguments");
	check_file_extension(av[1]);
	open_and_fill_map(&g, av);
	g.moves = 0;
	g.colected_count = 0;
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
	mlx_loop(g.mlx);
	return (0);
}

//erreur syscall Xlib (libx11 d'apres chatgpt)
//norme PARSE_MAP

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	t_g	g;

// 	open_and_fill_map(&g, av);
// 	for (int i = 0; i < g.map_height; i++)
//     {
//         printf("%s", g.map[i]); // Les lignes retournées par gnl incluent le '\n'
//         free(g.map[i]); // Libérer la mémoire allouée par gnl
//     }
// 	printf("\n");
//     free(g.map); // Libérer le tableau de la carte
//     return (0);
// }