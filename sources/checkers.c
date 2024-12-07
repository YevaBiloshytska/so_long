/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:08:13 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/12/04 23:19:39 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_items_accessibility(t_game *game, char V)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_rows)
	{
		j = 0;
		while (j < game->map_cols)
		{
			if ((game->map[i][j] == V && \
				!game->visited[i][j]))
			{
				free_visited(game);
				exit_game (game, "Error\nSome items or the "
					"exit are not accessible!");
			}
			j++;
		}
		i++;
	}
}

void	check_accessibility(t_game *game)
{
	init_visited(game);
	bfs(game, check_path_to, 'P');
	check_items_accessibility(game, 'C');
	free_visited(game);
	init_visited(game);
	bfs(game, check_path_to, 'E');
	check_items_accessibility(game, 'E');
	free_visited(game);
}

void	check_rectangular_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_rows - 1)
	{
		if ((size_t)ft_strlen(game->map[i]) - 1 != (size_t)game->map_cols)
			exit_game (game, "Error\nMap is not rectangular.");
		i++;
	}
}

void	check_valid_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_rows)
	{
		j = 0;
		while (j < game->map_cols)
		{
			if (game->map[i][j] != '1' && game->map[i][j] != '0' && \
				game->map[i][j] != 'C' && game->map[i][j] != 'E' && \
				game->map[i][j] != 'P')
				exit_game (game, "Error\nInvalid character in map.");
			j++;
		}
		i++;
	}
}

void	check_map_closed(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_cols)
	{
		if (game->map[0][i] != '1' || game->map[game->map_rows - 1][i] != '1')
			exit_game (game, "Error\nMap is not surrounded by walls.");
		i++;
	}
	i = 0;
	while (i < game->map_rows)
	{
		if (game->map[i][0] != '1' || game->map[i][game->map_cols - 1] != '1')
			exit_game (game, "Error\nMap is not surrounded by walls.");
		i++;
	}
}
