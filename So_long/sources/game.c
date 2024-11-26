/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:39:07 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/25 17:22:12 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_game(t_game *game) {
    game->MAP_WALL_img = mlx_xpm_file_to_image(game->mlx, WALL, &game->img_width, &game->img_height);
	game->MAP_FLOOR_img = mlx_xpm_file_to_image(game->mlx, FLOOR, &game->img_width, &game->img_height);
	game->MAP_HEART_img = mlx_xpm_file_to_image(game->mlx, HEART, &game->img_width, &game->img_height);
	game->MAP_EXIT_img = mlx_xpm_file_to_image(game->mlx, EXIT, &game->img_width, &game->img_height);
	game->MAP_PLAYER_img = mlx_xpm_file_to_image(game->mlx, PLAYER, &game->img_width, &game->img_height);

	if (!game->MAP_PLAYER_img)
    	exit_error("Failed to load player image.");
	game->total_MAP_HEARTs = count_elements(game->map, game->map_rows, game->map_cols, 'C');
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
    if (game->player_x + x_offset < 0 || game->player_x + x_offset >= game->map_cols || game->player_y + y_offset < 0 || game->player_y + y_offset >= game->map_rows)
        return;
    char target_cell = game->map[game->player_y + y_offset][game->player_x + x_offset];
    if (target_cell == '1')
        return;
	else if (target_cell == 'E')
	{
		if (game->collected_count < game->total_MAP_HEARTs)
			return;
		printf("You win! Exiting the game...\n");
		exit_game(game);
	}
    if (target_cell == 'C')
        game->collected_count++;
    game->map[game->player_y][game->player_x] = '0';
    game->player_x += x_offset;
    game->player_y += y_offset;
    game->map[game->player_y][game->player_x] = 'P';
    game->move_count++;
    printf("Moves: %d\n", game->move_count);
}










