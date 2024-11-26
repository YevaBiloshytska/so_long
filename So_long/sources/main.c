/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:49:22 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/26 12:37:32 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        exit_error("Error\nUsage: ./so_long map.ber");
    t_game game;
    game.move_count = 0;
    game.mlx = mlx_init();
    if (!game.mlx)
        exit_error("Failed to initialize mlx.");
    load_map(argv[1], &game);
    validate_map(game.map, game.map_rows, game.map_cols);
    game.win = mlx_new_window(game.mlx, game.map_cols * TILE_SIZE, game.map_rows * TILE_SIZE, "So Long");
    if (!game.win)
        exit_error("Failed to create window.");
    game.collected_count = 0;
    init_game(&game);
	draw_map(&game);
    mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
    mlx_loop(game.mlx);
}

