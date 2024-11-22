/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:49:22 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/22 17:02:05 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int key_hook(int keycode, t_game *game)
{
    if (keycode == 65307) // ESC
        exit_game(game);
    if (keycode == 119) // W
        move_player(game, 0, -1); // Вверх
    else if (keycode == 97) // A
        move_player(game, -1, 0); // Влево
    else if (keycode == 115) // S
        move_player(game, 0, 1); // Вниз
    else if (keycode == 100) // D
        move_player(game, 1, 0); // Вправо

    draw_map(game); // Перерисовываем карту
    return 0;
}


int main(int argc, char **argv)
{
    if (argc != 2)
        exit_error("Usage: ./so_long map.ber");

    t_game game;
    game.move_count = 0;
    game.mlx = mlx_init();
    if (!game.mlx)
        exit_error("Failed to initialize mlx.");

    load_map(argv[1], &game); // Загрузка карты
    validate_map(game.map, game.map_rows, game.map_cols); // Проверка карты

    // Размер клетки
    int cell_size = 32; // Размер клетки в пикселях

    // Устанавливаем размеры окна в зависимости от размера карты
    int window_width = game.map_cols * cell_size;
    int window_height = game.map_rows * cell_size;

    // Создаем окно с вычисленными размерами
    game.win = mlx_new_window(game.mlx, window_width, window_height, "So Long");

    if (!game.win)
    {
        exit_error("Failed to create window.");
    }

    game.collected_count = 0;

    init_game(&game); // Инициализация игры
    draw_map(&game); // Отрисовка карты

    mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
    mlx_loop(game.mlx);

    return 0;
}

