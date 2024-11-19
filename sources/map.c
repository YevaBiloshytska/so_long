/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <nikolly19.12@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:39:43 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/13 22:19:09 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_map(t_game *game)
{
    int i;
    int j;
    for (i = 0; i < game->map_rows; i++)
    {
        for (j = 0; j < game->map_cols; j++)
        {
            if (game->map[i][j] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall_img, j * TILE_SIZE, i * TILE_SIZE);
            else if (game->map[i][j] == '0')
                mlx_put_image_to_window(game->mlx, game->win, game->empty_img, j * TILE_SIZE, i * TILE_SIZE);
            else if (game->map[i][j] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, j * TILE_SIZE, i * TILE_SIZE);
            else if (game->map[i][j] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->exit_img, j * TILE_SIZE, i * TILE_SIZE);
            else if (game->map[i][j] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->player_img, j * TILE_SIZE, i * TILE_SIZE);
        }
    }
}
