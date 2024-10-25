/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_positions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:49:24 by root              #+#    #+#             */
/*   Updated: 2024/10/25 13:53:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void get_positions(int *x, int *y, int pos_x, int pos_y)
{
    *x = pos_x * SIZE;
    *y = pos_y * SIZE;
}

void get_all_mobs(t_game *game)
{
    int i, j;

    game->mob_count = 0;
    i = 0;
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == 'M')
                game->mob_count++;
            j++;
        }
        i++;
    }
    game->mobs = malloc(sizeof(int *) * game->mob_count);
    if (!game->mobs)
    {
        free_game_resources(game);
        handle_error("Allocation error for mobs");
    }
    i = 0;
    while (i < game->mob_count)
    {
        game->mobs[i] = malloc(sizeof(int) * 2);
        if (!game->mobs[i])
        {
            free_game_resources(game);
            handle_error("Allocation error for mobs coordinates");
        }
        i++;
    }
}

void get_all_col(t_game *game)
{
    int i;
    int j;
    int index = 0;

    game->col = malloc(sizeof(int *) * game->c_count);
    if (!game->col)
    {
        free_game_resources(game);
        handle_error("Allocation error for collectibles");
    }
    i = 0;
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == 'C')
            {
                game->col[index] = malloc(sizeof(int) * 2);  // Stockage des coordonnées (x, y)
                if (!game->col[index])
                {
                    free_game_resources(game);
                    handle_error("Allocation error for collectible coordinates");
                }
                game->col[index][0] = j;  // x-coordinate
                game->col[index][1] = i;  // y-coordinate
                index++;
            }
            j++;
        }
        i++;
    }
}

void check_every_position(t_game *game)
{
    int i;
    int j;
    int m_idx;
    int c_idx;

    m_idx = 0;
    c_idx = 0;
    i = 0;
    get_all_mobs(game);
    get_all_col(game);
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == 'C')
            {
                get_positions(&game->col[c_idx][0], &game->col[c_idx][1], j, i);
                c_idx++;
            }
            if (game->map[i][j] == 'P')
                get_positions(&game->player_x, &game->player_y, j, i);
            if (game->map[i][j] == 'M')
            {
                get_positions(&game->mobs[m_idx][0], &game->mobs[m_idx][1], j, i);
                m_idx++;
            }
            if (game->map[i][j] == 'E')
                get_positions(&game->exit_x, &game->exit_y, j, i);
            j++;
        }
        i++;
    }
}
