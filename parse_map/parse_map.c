/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:22:21 by root              #+#    #+#             */
/*   Updated: 2024/10/24 16:26:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	check_player(t_game *game, int fd)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	check = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
				check++;
			j++;
		}
		i++;
	}
	if (check == 0)
		handle_error_close_free("Not enough player!", fd, game->map);
	else if (check > 1)
		handle_error_close_free("Too many players!", fd, game->map);
}

static void	check_exit(t_game *game, int fd)
{
	int	i;
	int	j;
	int	check;

	i = 0;;
	check = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'E')
				check++;
			j++;
		}
		i++;
	}
	if (check == 0)
		handle_error_close_free("You forgot the exit!", fd, game->map);
	else if (check > 1)
		handle_error_close_free("Too many exit!", fd, game->map);
}

static void	check_item(t_game *game, int fd)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	check = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'C')
				check++;
			j++;
		}
		i++;
	}
	if (check < 1)
		handle_error_close_free("No items detected!", fd, game->map);
}

static void check_if_char_is_known(char c, int fd, t_game *game)
{
	if (c != '1' && c != '0' && c != 'P' && c != 'C' && 
	c != 'E' && c != 'M' && c != '\n') //gerer le retour a la ligne plsu tard
		handle_error_close_free("Characters aren't known!", fd, game->map);
}

static void check_char(t_game *game, int fd)
{
    int i;
    int j;

    i = 0;
    game->c_count = 0;  // Initialise le nombre de collectables ici
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == 'P')
            {
                game->player_x = j * SIZE;
                game->player_y = i * SIZE;
            }
            if (game->map[i][j] == 'C')  // Compter les collectables
                game->c_count++;
            check_if_char_is_known(game->map[i][j], fd, game);  // Vérifie les caractères
            j++;
        }
        i++;
    }
}


static void	check_rest(t_game *game, int fd)
{
	check_walls(game, fd);
	check_player(game, fd);
	check_item(game, fd);
	check_exit(game, fd);
	check_char(game, fd);
	if (!is_map_solvable(game))
		handle_error_close_free("The map is not solvable!", fd, game->map);
}

void	open_and_fill_map(t_game *game, char **av)
{
	int		i;
	int		fd;

	i = 0;
	game->map_height = count_line(av[1]);
	game->map_width = count_collumns(av[1]);
	game->map = malloc(sizeof(char *) * (game->map_height + 1)); // a voir pour le +1
	if (!game->map)
		return;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("L'ouverture de la map a échoué!");
		exit(EXIT_FAILURE);
	}
	while ((game->map[i] = get_next_line(fd)) != NULL)
		i++;
	game->map[i] = NULL;
	check_rest(game, fd);
	close(fd);
}

//Leak si il n'y a pas le nombre de collone
// Voir map5.ber, leak venant gnl