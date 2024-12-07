/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:39:43 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/12/04 13:13:41 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_img(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x, y);
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_rows)
	{
		j = 0;
		while (j < game->map_cols)
		{
			if (game->map[i][j] == '1')
				put_img(game, game->wall_img, j * SIZE, i * SIZE);
			else if (game->map[i][j] == '0')
				put_img(game, game->floor_img, j * SIZE, i * SIZE);
			else if (game->map[i][j] == 'C')
				put_img(game, game->heart_img, j * SIZE, i * SIZE);
			else if (game->map[i][j] == 'E')
				put_img(game, game->exit_img, j * SIZE, i * SIZE);
			else if (game->map[i][j] == 'P')
				put_img(game, game->player_img, j * SIZE, i * SIZE);
			j++;
		}
		i++;
	}
}
