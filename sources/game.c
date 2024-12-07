/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:39:07 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/12/04 13:32:17 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game)
{
	int	img_width;
	int	img_height;

	game->wall_img = mlx_xpm_file_to_image(game->mlx, WALL, \
									&img_width, &img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, FLOOR, \
									&img_width, &img_height);
	game->heart_img = mlx_xpm_file_to_image(game->mlx, HEART, \
									&img_width, &img_height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, EXIT, \
									&img_width, &img_height);
	game->player_img = mlx_xpm_file_to_image(game->mlx, PLAYER, \
									&img_width, &img_height);
	if (!game->player_img)
		exit_game (game, "Error\nFailed to load player image.");
}

void	exit_game(t_game *game, const char *msg)
{
	ft_printf(msg);
	free_textures(game);
	if (game->map)
	{
		free_map(game->map, game->map_rows);
		game->map = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	exit(0);
}

int	close_window(t_game *game)
{
	exit_game(game, "");
	return (0);
}

void	move_player(t_game *game, int x_set, int y_set)
{
	char	target_cell;

	if (game->player_x + x_set < 0 || \
		game->player_x + x_set >= game->map_cols || \
		game->player_y + y_set < 0 || \
		game->player_y + y_set >= game->map_rows)
		return ;
	target_cell = game->map[game->player_y + y_set][game->player_x + x_set];
	if (target_cell == '1')
		return ;
	else if (target_cell == 'E')
	{
		if (game->collected_count < game->total_hearts)
			return ;
		exit_game(game, "You win! Exiting the game...\n");
	}
	if (target_cell == 'C')
		game->collected_count++;
	game->map[game->player_y][game->player_x] = '0';
	game->player_x += x_set;
	game->player_y += y_set;
	game->map[game->player_y][game->player_x] = 'P';
	game->move_count++;
	ft_printf("Moves: %d\n", game->move_count);
}
