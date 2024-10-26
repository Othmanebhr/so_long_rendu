/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:48:00 by root              #+#    #+#             */
/*   Updated: 2024/10/26 21:22:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	allocate_mobs(t_game *g)
{
	int	i;

	g->mobs = malloc(sizeof(int *) * g->mob_count);
	if (!g->mobs)
	{
		free_game_resources(g);
		handle_error("Allocation error for mobs");
	}
	i = 0;
	while (i < g->mob_count)
	{
		g->mobs[i] = malloc(sizeof(int) * 2);
		if (!g->mobs[i])
		{
			free_game_resources(g);
			handle_error("Allocation error for mobs coordinates");
		}
		i++;
	}
}

void	get_all_mobs(t_game *g)
{
	int	i;
	int	j;

	g->mob_count = 0;
	i = 0;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == 'M')
				g->mob_count++;
			j++;
		}
		i++;
	}
	allocate_mobs(g);
}

static void	store_col(t_game *g, int j, int i, int *index)
{
	g->col[*index] = malloc(sizeof(int) * 2);// Stockage des coordonnées (x, y)
	if (!g->col[*index])
	{
		free_game_resources(g);
		handle_error("Allocation error for collectible coordinates");
	}
	g->col[*index][0] = j;// x-coordinate
	g->col[*index][1] = i;// y-coordinate
	(*index)++;
}

void	get_all_col(t_game *g)
{
	int	i;
	int	j;
	int	index;

	index = 0;
	g->col = malloc(sizeof(int *) * g->c_count);
	if (!g->col)
	{
		free_game_resources(g);
		handle_error("Allocation error for collectibles");
	}
	i = 0;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == 'C')
				store_col(g, j, i, &index);
			j++;
		}
		i++;
	}
}
