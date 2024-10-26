/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:22:21 by root              #+#    #+#             */
/*   Updated: 2024/10/26 21:37:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	check_player(t_game *g, int fd)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	check = 0;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == 'P')
				check++;
			j++;
		}
		i++;
	}
	if (check == 0)
		handle_error_close_free("Not enough player!", fd, g->map);
	else if (check > 1)
		handle_error_close_free("Too many players!", fd, g->map);
}

static void	check_exit(t_game *g, int fd)
{
	int	i;
	int	j;
	int	check;

	i = 0;;
	check = 0;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == 'E')
				check++;
			j++;
		}
		i++;
	}
	if (check == 0)
		handle_error_close_free("You forgot the exit!", fd, g->map);
	else if (check > 1)
		handle_error_close_free("Too many exit!", fd, g->map);
}

static void	check_item(t_game *g, int fd)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	check = 0;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == 'C')
				check++;
			j++;
		}
		i++;
	}
	if (check < 1)
		handle_error_close_free("No items detected!", fd, g->map);
}

static void	check_if_char_is_known(char c, int fd, t_game *g)
{
	if (c != '1' && c != '0' && c != 'P' && c != 'C'
		&& c != 'E' && c != 'M' && c != '\n')
		handle_error_close_free("Characters aren't known!", fd, g->map);
}

static void	check_char(t_game *g, int fd)
{
	int	i;
	int	j;

	i = 0;
	g->c_count = 0;  // Initialise le nombre de collectables ici
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == 'P')
			{
				g->player_x = j * SIZE;
				g->player_y = i * SIZE;
			}
			if (g->map[i][j] == 'C')  // Compter les collectables
				g->c_count++;
			check_if_char_is_known(g->map[i][j], fd, g);  // Vérifie les caractères
			j++;
		}
		i++;
	}
}

static void	check_rest(t_game *g, int fd)
{
	check_walls(g, fd);
	check_player(g, fd);
	check_item(g, fd);
	check_exit(g, fd);
	check_char(g, fd);
	if (!is_map_solvable(g))
		handle_error_close_free("The map is not solvable!", fd, g->map);
}

void	open_and_fill_map(t_game *g, char **av)
{
	int		i;
	int		fd;

	i = 0;
	g->map_height = count_line(av[1]);
	g->map_width = count_collumns(av[1]);
	g->map = malloc(sizeof(char *) * (g->map_height + 1)); // a voir pour le +1
	if (!g->map)
		return ;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("L'ouverture de la map a échoué!");
		exit(EXIT_FAILURE);
	}
	while ((g->map[i] = get_next_line(fd)) != NULL)
		i++;
	g->map[i] = NULL;
	check_rest(g, fd);
	close(fd);
}
