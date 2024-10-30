/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:22:21 by root              #+#    #+#             */
/*   Updated: 2024/10/27 15:49:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
	g->map = malloc(sizeof(char *) * (g->map_height + 1));
	if (!g->map)
		return ;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("L'ouverture de la map a échoué!");
		exit(EXIT_FAILURE);
	}
	g->map[i] = get_next_line(fd);
	while (g->map[i] != NULL)
	{
		i++;
		g->map[i] = get_next_line(fd);
	}
	g->map[i] = NULL;
	check_rest(g, fd);
	close(fd);
}
