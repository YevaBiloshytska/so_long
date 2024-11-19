/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <nikolly19.12@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:49:22 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/13 20:55:33 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int key_hook(int keycode, t_game *game)
{
    if (keycode == 65307) // ESC
        exit_game(game);
    if (keycode == 119) // W
        move_player(game, 0, -1); // Вверх
    if (keycode == 97) // A
        move_player(game, -1, 0); // Влево
    if (keycode == 115) // S
        move_player(game, 0, 1); // Вниз
    if (keycode == 100) // D
        move_player(game, 1, 0); // Вправо
    draw_map(game); // Перерисовать карту
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        exit_error("Usage: ./so_long map.ber");

    t_game game;
    game.mlx = mlx_init();
    if (!game.mlx)
        exit_error("Failed to initialize mlx.");
    game.win = mlx_new_window(game.mlx, 800, 600, "So Long");
    if (!game.win)
        exit_error("Failed to create window.");
    
    init_game(&game);

    load_map(argv[1], &game); // Загрузка карты
    validate_map(game.map, game.map_rows, game.map_cols); // Проверка карты
    draw_map(&game); // Отрисовка карты

    mlx_key_hook(game.win, key_hook, &game);
    mlx_loop(game.mlx);

    return 0;
}
