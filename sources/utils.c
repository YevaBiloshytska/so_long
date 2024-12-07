/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:11:17 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/12/05 18:49:03 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_and_validate_file(t_game *game, const char *filename)
{
	const char	*ext;
	size_t		len;

	ext = ".ber";
	if (!filename)
		exit_game(game, "Error\nInvalid file name.");
	len = strlen(filename);
	if (len < 4 || strncmp(&filename[len - 4], ext, 4) != 0)
		exit_game(game, "Error\nFile must end with .ber.");
	game->fd = open(filename, O_RDONLY);
	if (game->fd == -1)
		exit_game(game, "Error\nNo such file or cannot open.");
	return (game->fd);
}

void	check_map_size(t_game *game)
{
	int		screen_width;
	int		screen_height;
	int		map_width;
	int		map_height;

	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	map_width = game->map_cols * SIZE;
	map_height = game->map_rows * SIZE;
	if (map_width > screen_width || map_height > screen_height - 80)
		exit_game(game, "Error\nMap is too large for the screen.");
}
