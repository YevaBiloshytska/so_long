/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <nikolly19.12@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:39:07 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/13 21:13:39 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>

void exit_error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}


void init_game(t_game *game) {
    game->img_width = 32;
    game->img_height = 32;

    game->wall_img = mlx_xpm_file_to_image(game->mlx, WALL, &game->img_width, &game->img_height);
    game->empty_img = mlx_xpm_file_to_image(game->mlx, FLOOR, &game->img_width, &game->img_height);
    game->collectible_img = mlx_xpm_file_to_image(game->mlx, HEART, &game->img_width, &game->img_height);
    game->exit_img = mlx_xpm_file_to_image(game->mlx, EXIT, &game->img_width, &game->img_height);
    game->player_img = mlx_xpm_file_to_image(game->mlx, PLAYER, &game->img_width, &game->img_height);
}
void free_textures(t_game *game) {
    if (game->wall_img) mlx_destroy_image(game->mlx, game->wall_img);
    if (game->empty_img) mlx_destroy_image(game->mlx, game->empty_img);
    if (game->collectible_img) mlx_destroy_image(game->mlx, game->collectible_img);
    if (game->exit_img) mlx_destroy_image(game->mlx, game->exit_img);
    if (game->player_img) mlx_destroy_image(game->mlx, game->player_img);
}

void exit_game(t_game *game) {
    close_game(game);
    free_map(game->map); // Очистка карты
    exit(0); // Завершение игры
}

void close_game(t_game *game) {
    free_textures(game); // Освобождение текстур
    if (game->win) mlx_destroy_window(game->mlx, game->win);
    //if (game->mlx) mlx_destroy_display(game->mlx);
    free(game->mlx);
}

void free_map(char **map) {
    int i = 0;
    while (map[i]) {
        free(map[i]);
        i++;
    }
    free(map);
}

int check_win_condition(t_game *game)
{
    if (game->collected_count == game->total_collectibles)
    {
        mlx_string_put(game->mlx, game->win, game->map_cols * TILE_SIZE / 2, game->map_rows * TILE_SIZE / 2, 0xFFFFFF, "You Win!");
        return 1;
    }
    return 0;
}

void move_player(t_game *game, int x_offset, int y_offset)
{
    int new_x = game->player_x + x_offset;
    int new_y = game->player_y + y_offset;

    if (game->map[new_y][new_x] != '1') // Проверка на стену
    {
        if (game->map[new_y][new_x] == 'C') // Коллекционный предмет
        {
            game->collected_count++;
        }
        if (game->map[new_y][new_x] == 'E' && game->collected_count == game->total_collectibles) // Выход и победа
        {
            if (check_win_condition(game))
                return;
        }
        game->player_x = new_x;
        game->player_y = new_y;
    }
}
