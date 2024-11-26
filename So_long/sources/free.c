/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:44:29 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/26 16:44:02 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_textures(t_game *game) {
    if (game->MAP_WALL_img) mlx_destroy_image(game->mlx, game->MAP_WALL_img);
    if (game->MAP_FLOOR_img) mlx_destroy_image(game->mlx, game->MAP_FLOOR_img);
    if (game->MAP_HEART_img) mlx_destroy_image(game->mlx, game->MAP_HEART_img);
    if (game->MAP_EXIT_img) mlx_destroy_image(game->mlx, game->MAP_EXIT_img);
    if (game->MAP_PLAYER_img) mlx_destroy_image(game->mlx, game->MAP_PLAYER_img);
}

void free_map(char **map, int rows)
{
	int i;

	i = 0;
	while(i < rows)
	{
		free(map[i]); // Освобождаем каждую строку карты
		i++;
	}
    free(map); // Освобождаем сам массив указателей
}

void free_visited(t_game *game, bool **visited)
{
    int i = 0;
    while (i < game->map_rows) {
        free(visited[i]);
        i++;
    }
    free(visited);
}