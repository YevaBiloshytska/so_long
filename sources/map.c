/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:39:43 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/21 21:03:11 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_map(t_game *game)
{
    int i, j;
    for (i = 0; i < game->map_rows; i++) {
        for (j = 0; j < game->map_cols; j++) {
            // Отрисовываем стены
            if (game->map[i][j] == '1') {
                mlx_put_image_to_window(game->mlx, game->win, game->MAP_WALL_img, j * TILE_SIZE, i * TILE_SIZE);
            }
            // Отрисовываем пустое пространство
            else if (game->map[i][j] == '0') {
                mlx_put_image_to_window(game->mlx, game->win, game->MAP_FLOOR_img, j * TILE_SIZE, i * TILE_SIZE);
            }
            // Отрисовываем коллекционные предметы
            else if (game->map[i][j] == 'C') {
                mlx_put_image_to_window(game->mlx, game->win, game->MAP_HEART_img, j * TILE_SIZE, i * TILE_SIZE);
            }
            // Отрисовываем выход
            else if (game->map[i][j] == 'E') {
                mlx_put_image_to_window(game->mlx, game->win, game->MAP_EXIT_img, j * TILE_SIZE, i * TILE_SIZE);
            }
            // Отрисовываем игрока
            else if (game->map[i][j] == 'P') {
                mlx_put_image_to_window(game->mlx, game->win, game->MAP_PLAYER_img, j * TILE_SIZE, i * TILE_SIZE);
            }
        }
    }
}
