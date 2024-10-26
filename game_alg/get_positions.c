/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_positions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:49:24 by root              #+#    #+#             */
/*   Updated: 2024/10/26 21:26:23 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	get_positions(int *x, int *y, int pos_x, int pos_y)
{
	*x = pos_x * SIZE;
	*y = pos_y * SIZE;
}

static void	check_mobs(t_game *g, int j, int i, int *m_idx)
{
	if (g->map[i][j] == 'M')
	{
		get_positions(&g->mobs[*m_idx][0], &g->mobs[*m_idx][1], j, i);
		(*m_idx)++;
	}
}

static void	check_cols(t_game *g, int j, int i, int *c_idx)
{
	if (g->map[i][j] == 'C')
	{
		get_positions(&g->col[*c_idx][0], &g->col[*c_idx][1], j, i);
		(*c_idx)++;
	}
}

void	check_every_position(t_game *g)
{
	int	i;
	int	j;
	int	m_idx;
	int	c_idx;

	m_idx = 0;
	c_idx = 0;
	i = 0;
	get_all_mobs(g);
	get_all_col(g);
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			check_cols(g, j, i, &c_idx);
			check_mobs(g, j, i, &m_idx);
			if (g->map[i][j] == 'P')
				get_positions(&g->player_x, &g->player_y, j, i);
			if (g->map[i][j] == 'E')
				get_positions(&g->exit_x, &g->exit_y, j, i);
			j++;
		}
		i++;
	}
}
