/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:49:22 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/12/05 21:23:39 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	game = (t_game){0};
	if (argc != 2)
		exit_game (&game, "Error\nUsage: ./so_long map.ber");
	game.mlx = mlx_init();
	if (!game.mlx)
		exit_game (&game, "Error\nFailed to initialize mlx.");
	load_map(argv[1], &game);
	validate_map(&game);
	game.win = mlx_new_window(game.mlx, game.map_cols * SIZE, \
								game.map_rows * SIZE, "So Long");
	if (!game.win)
		exit_game (&game, "Error\nFailed to create window.");
	init_game(&game);
	draw_map(&game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}
