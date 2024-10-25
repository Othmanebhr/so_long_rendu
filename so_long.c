/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:03:18 by root              #+#    #+#             */
/*   Updated: 2024/10/25 13:41:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void check_file_extension(char *filename)
{
    int len;
    
    len = ft_strlen(filename);
    if (len < 4 || ft_strcmp(filename + len - 4, ".ber") != 0)
        handle_error("The file must have a .ber extension");
}

static void init_game(t_game *game)
{
    // game->c_count = 0;
    game->colected_count = 0;
    // game->moves = 0;
    // game->player_x = 0;
    // game->player_y = 0;
    // game->map = NULL;
    // game->col = NULL;
}


int main(int ac, char **av)
{
    t_game game;

    if (ac > 2)
        handle_error("Too much arguments");
    if (ac < 2)
        handle_error("Too few arguments");
    check_file_extension(av[1]);
    open_and_fill_map(&game, av);
    game.moves = 0;
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        free_game_resources(&game);
        handle_error("Failed to initialize mlx");
    }
    game.win = mlx_new_window(game.mlx, game.map_width * SIZE, game.map_height *SIZE, "so_long");
    init_game(&game);
    load_img(&game);
    check_every_position(&game);
    render_map(&game, game.map);
    mlx_key_hook(game.win, key_hook, &game);
    mlx_loop(game.mlx);
    return (0);
}

//erreur syscall Xlib (libx11 d'apres chatgpt)

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	t_game	game;

// 	open_and_fill_map(&game, av);
// 	for (int i = 0; i < game.map_height; i++)
//     {
//         printf("%s", game.map[i]); // Les lignes retournées par gnl incluent le '\n'
//         free(game.map[i]); // Libérer la mémoire allouée par gnl
//     }
// 	printf("\n");
//     free(game.map); // Libérer le tableau de la carte
//     return (0);
// }