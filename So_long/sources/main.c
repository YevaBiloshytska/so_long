/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:49:22 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/24 17:29:50 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        exit_error("Error\nUsage: ./so_long map.ber");
    t_game game; //Создаётся структура t_game для хранения состояния игры.
    game.move_count = 0; //счетчик шагов
    game.mlx = mlx_init();//Здесь инициализируется MiniLibX.Функция mlx_init() устанавливает соединение с графическим сервером, таким как X11 (на Linux).
    if (!game.mlx)//Если это не удалось, игра завершится с сообщением об ошибке.
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

