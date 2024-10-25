/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:16:28 by root              #+#    #+#             */
/*   Updated: 2024/10/25 13:40:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

# define SIZE 64

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		**mobs;
	int		mob_count;
	int		**col;
	int		c_count;
	int		exit_x;
	int		exit_y;
	void	*wall_img;
	void	*floor_img;
	void	*player_img;
	void	*mob_img;
	void	*exit_img;
	void	*collectible_img;
	int		moves;
}	t_game;

//parse Map
void	open_and_fill_map(t_game *game, char **av);
void	check_walls(t_game	*game, int fd);
int		count_line(char	*file);
int		count_collumns(char *file);
int		is_map_solvable(t_game *game);

//utils
void	handle_error(char *str);
void	handle_error_close(char *str, int fd);
void	handle_error_close_free(char *str, int fd, char **map);

//alg
void	check_every_position(t_game *game);
int		key_hook(int keycode, t_game *game);

//Img
void	load_img(t_game *game);
void	render_map(t_game *game, char **map);

//End game
void	game_win(t_game *game);
void	game_over(t_game *game);
void	free_game_resources(t_game *game);

#endif