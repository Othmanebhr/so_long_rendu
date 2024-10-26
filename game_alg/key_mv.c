/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:37:35 by root              #+#    #+#             */
/*   Updated: 2024/10/26 21:29:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	display_move_count(t_game *g)
{
	char	*str;
	char	*s;

	str = ft_itoa(g->moves);
	s = ft_strjoin("Mouvement", str);
	mlx_string_put(g->mlx, g->win, 10, 10, 0xFFFFFF, s); // Afficher le compteur
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
	// Vérifier les limites de la carte et les collisions avec les murs
	if (new_x >= 0 && new_x < g->map_width * SIZE
		&& new_y >= 0 && new_y < g->map_height * SIZE)
	{
		if (g->map[new_y / SIZE][new_x / SIZE] != '1') // Si ce n'est pas un mur
			check_action(new_x, new_y, g);  
	}
}

int	key_hook(int keycode, t_game *g)
{
	int new_x;
	int new_y;

	new_x = g->player_x;
	new_y = g->player_y;
	if (keycode == 65307) // Touche Echap pour quitter
	{
		// mlx_destroy_window(g->mlx, g->win);
		free_game_resources(g);
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
	check_if_walls(new_x, new_y, g);
	return (0);
}
