/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:37:35 by root              #+#    #+#             */
/*   Updated: 2024/10/25 14:08:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void display_move_count(t_game *game) 
{
    char *str = ft_itoa(game->moves);
    char *s = ft_strjoin("Mouvement", str);
    mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, s); // Afficher le compteur
    free(str);
    free(s);
}

static void check_action(int new_x, int new_y, t_game *game)
{
    if (game->map[new_y / SIZE][new_x / SIZE] == '0' 
        || game->map[new_y / SIZE][new_x / SIZE] == 'P' )
    {
        mlx_put_image_to_window(game->mlx, game->win, game->floor_img, game->player_x, game->player_y);
        game->player_x = new_x;
        game->player_y = new_y;
        game->moves++;
        display_move_count(game);
        ft_printf("Moves: %d\n", game->moves);
        mlx_put_image_to_window(game->mlx, game->win, game->player_img, game->player_x, game->player_y);
    }
    if (game->map[new_y / SIZE][new_x / SIZE] == 'M')
        game_over(game);
    if (game->map[new_y / SIZE][new_x / SIZE] == 'C')
    {
        mlx_put_image_to_window(game->mlx, game->win, game->floor_img, game->player_x, game->player_y);
        game->player_x = new_x;
        game->player_y = new_y;
        mlx_put_image_to_window(game->mlx, game->win, game->player_img, game->player_x, game->player_y);
        game->map[new_y / SIZE][new_x / SIZE] = '0';
        game->colected_count++;
        ft_printf("collectible restant: %d\n", game->c_count - game->colected_count);
    }
    if (game->map[new_y / SIZE][new_x / SIZE] == 'E')
    {
        if (game->c_count == game->colected_count)
            game_win(game);
    }
}// Parfois la sortie ne marche pas, le point de depart n'est plus accessible

static void check_if_walls(int new_x, int new_y, t_game *game)
{
    // Vérifier les limites de la carte et les collisions avec les murs
    if (new_x >= 0 && new_x < game->map_width * SIZE 
        && new_y >= 0 && new_y < game->map_height * SIZE)
    {
        if (game->map[new_y / SIZE][new_x / SIZE] != '1') // Si ce n'est pas un mur
            check_action(new_x, new_y, game);  
    }
}

int key_hook(int keycode, t_game *game)
{
    int new_x;
    int new_y;

    new_x = game->player_x;
    new_y = game->player_y;
    if (keycode == 65307) // Touche Echap pour quitter
    {
        // mlx_destroy_window(game->mlx, game->win);
        free_game_resources(game);
        exit(EXIT_SUCCESS);
    }
    if (keycode == 65361) // Flèche gauche
        new_x -= SIZE;
    else if (keycode == 65363) // Flèche droite
        new_x += SIZE;
    else if (keycode == 65362) // Flèche haut
        new_y -= SIZE;
    else if (keycode == 65364) // Flèche bas
        new_y += SIZE;
    check_if_walls(new_x, new_y, game);
    return (0);
}
