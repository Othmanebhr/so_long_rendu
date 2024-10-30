/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_everithing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:32:01 by root              #+#    #+#             */
/*   Updated: 2024/10/27 15:32:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_player(t_game *g, int fd)
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

void	check_exit(t_game *g, int fd)
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

void	check_item(t_game *g, int fd)
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

void	check_if_char_is_known(char c, int fd, t_game *g)
{
	if (c != '1' && c != '0' && c != 'P' && c != 'C'
		&& c != 'E' && c != 'M' && c != '\n')
		handle_error_close_free("Characters aren't known!", fd, g->map);
}

void	check_char(t_game *g, int fd)
{
	int	i;
	int	j;

	i = 0;
	g->c_count = 0;
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
			if (g->map[i][j] == 'C')
				g->c_count++;
			check_if_char_is_known(g->map[i][j], fd, g);
			j++;
		}
		i++;
	}
}
