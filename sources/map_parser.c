/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:37:04 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/12/05 21:35:34 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_rows)
	{
		j = 0;
		while (j < game->map_cols)
		{
			if (game->map[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	load_map(const char *filename, t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	open_and_validate_file(game, filename);
	count(game);
	close(game->fd);
	open_and_validate_file(game, filename);
	line = get_next_line(game->fd);
	game->map = malloc((game->map_rows + 1) * sizeof(char *));
	if (!game->map)
	{
		exit_game(game, "Error\nFailed to allocate memory for map.");
	}
	while (line != NULL)
	{
		game->map[i] = line;
		if (!game->map[i])
			exit_game(game, "Error\nFailed to allocate memory for map row.");
		line = get_next_line(game->fd);
		i++;
	}
	close(game->fd);
	find_player_position(game);
}

int	count_elements(t_game *game, char element)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (i < game->map_rows)
	{
		j = 0;
		while (j < game->map_cols)
		{
			if (game->map[i][j] == element)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	validate_map(t_game *game)
{
	int	exit_count;
	int	player_c;

	exit_count = count_elements(game, 'E');
	player_c = count_elements(game, 'P');
	game->total_hearts = count_elements(game, 'C');
	if (game->map == NULL || game->map_rows <= 0 || game->map_cols <= 0)
		exit_game(game, "Error\nInvalid map or dimensions.");
	check_map_size(game);
	check_rectangular_map(game);
	check_map_closed(game);
	check_valid_characters(game);
	if (exit_count != 1 || player_c != 1 || game->total_hearts < 1)
		exit_game(game, "Error\nMap must contain exactly 1 exit, "
			"1 player, and at least 1 collectible.");
	check_accessibility(game);
}

void	count(t_game *game)
{
	char	*line;

	line = get_next_line(game->fd);
	while (line != NULL)
	{
		if (game->map_cols == 0)
			game->map_cols = ft_strlen(line) - 1;
		free(line);
		game->map_rows++;
		line = get_next_line(game->fd);
	}
}
