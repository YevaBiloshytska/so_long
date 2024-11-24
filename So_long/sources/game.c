/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:39:07 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/23 14:29:45 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_game(t_game *game) {
    game->img_width = 32;
    game->img_height = 32;

    game->MAP_WALL_img = mlx_xpm_file_to_image(game->mlx, WALL, &game->img_width, &game->img_height);
	game->MAP_FLOOR_img = mlx_xpm_file_to_image(game->mlx, FLOOR, &game->img_width, &game->img_height);
	game->MAP_HEART_img = mlx_xpm_file_to_image(game->mlx, HEART, &game->img_width, &game->img_height);
	game->MAP_EXIT_img = mlx_xpm_file_to_image(game->mlx, EXIT, &game->img_width, &game->img_height);
	game->MAP_PLAYER_img = mlx_xpm_file_to_image(game->mlx, PLAYER, &game->img_width, &game->img_height);

	if (!game->MAP_PLAYER_img)
    	exit_error("Failed to load player image.");
	game->total_MAP_HEARTs = 0;
	for (int i = 0; i < game->map_rows; i++) {
		for (int j = 0; j < game->map_cols; j++) {
			if (game->map[i][j] == 'C') {
				game->total_MAP_HEARTs++;
			}
		}
	}

	check_accessibility(game);
}

void exit_game(t_game *game) {
    free_map(game->map, game->map_rows); // Очистка карты
    free_textures(game); // Очистка текстур
    mlx_destroy_window(game->mlx, game->win); // Закрытие окна
    mlx_destroy_display(game->mlx); // Уничтожение дисплея
    free(game->mlx); // Освобождение памяти для mlx
    exit(0); // Завершаем игру
}

int close_window(t_game *game)
{
    exit_game(game); // Завершает игру и освобождает ресурсы
    return (0);
}

void move_player(t_game *game, int x_offset, int y_offset)
{
    int new_x = game->player_x + x_offset;
    int new_y = game->player_y + y_offset;

    // Проверка на выход за границы карты
    if (new_x < 0 || new_x >= game->map_cols || new_y < 0 || new_y >= game->map_rows)
        return; // Если новый индекс за пределами карты, не двигаемся

    char target_cell = game->map[new_y][new_x];

    // Проверка на стену
    if (target_cell == '1')
        return;

    // Проверка на выход (E), если не собраны все предметы
	if (target_cell == 'E') {
		// Если не собраны все предметы, не пускаем игрока на выход
		if (game->collected_count < game->total_MAP_HEARTs) {
			return; // Не пускаем на выход
		}

		// Если все предметы собраны и игрок стоит на выходе
		printf("You win! Exiting the game...\n");
		exit_game(game); // Завершаем игру
	}



    // Если на клетке коллекционный предмет
    if (target_cell == 'C') {
        game->collected_count++; // Увеличиваем счетчик собранных предметов
    }

    // Обновление карты: убираем игрока с предыдущей позиции
    game->map[game->player_y][game->player_x] = '0';

    // Устанавливаем игрока на новой позиции
    game->map[new_y][new_x] = 'P';

    // Обновляем координаты игрока
    game->player_x = new_x;
    game->player_y = new_y;

    // Увеличиваем счётчик движений
    game->move_count++;
    printf("Moves: %d\n", game->move_count);

    // Если игрок достиг выхода и собрал все предметы
    // Эта проверка теперь внутри блока выше
}










