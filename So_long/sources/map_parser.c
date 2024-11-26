/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:37:04 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/25 15:06:34 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int open_map_file(const char *filename)
{
    int fd;
	
	fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit_error("Error\nFailed to open map file.");
    return fd;
}

void load_map(const char *filename, t_game *game)
{
    char *line;
    int fd;

	game->map_rows = 0;
	game->map_cols = 0;
	game->map = NULL;
    game->total_collectibles = 0;
    fd = open_map_file(filename);
	line = get_next_line(fd);
    while (line != NULL)
	{
        if (game->map_cols == 0)
            game->map_cols = ft_strlen(line) - 1;
        game->map = realloc(game->map, (game->map_rows + 1) * sizeof(char *));
        if (!game->map)
            exit_error("Error\nMemory allocation failed.");
        game->map[game->map_rows] = line;
        game->map_rows++;
		line = get_next_line(fd);
    }
	find_player_position(game);
}

void find_player_position(t_game *game)
{
    int i;
    int j;

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
                return;
            }
            j++;
        }
        i++;
    }
}

void	check_map_closed(char **map, int rows, int cols)
{
    int i;

	i = 0;
	while(i < cols)
	{
        if (map[0][i] != '1' || map[rows - 1][i] != '1')
            exit_error("Error\nMap is not surrounded by walls.");		
		i++;
	}
	i = 0;
	while(i < rows)
	{
        if (map[i][0] != '1' || map[i][cols - 1] != '1')
            exit_error("Error\nMap is not surrounded by walls.");		
		i++;
	}
}

void check_valid_characters(char **map, int rows, int cols)
{
    int i;
	int j;

	i = 0;
	while(i < rows)
	{
		j = 0;
		while(j < cols)
		{
            if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'C' && map[i][j] != 'E' && map[i][j] != 'P')
                exit_error("Error\nInvalid character in map.");			
			j++;
		}
		i++;
	}
}

int count_elements(char **map, int rows, int cols, char element)
{
    int count;
	int i;
	int j;
	
	count = 0;
	i = 0;
	while(i < rows)
	{
		j = 0;
		while(j < cols)
		{
			if(map[i][j] == element)
				count++;
			j++;
		}
		i++;
	}
    return count;
}

void validate_map(char **map, int rows, int cols)
{
	int exit_count;
    int player_count;
    int collectible_count;

	exit_count = count_elements(map, rows, cols, 'E');
    player_count = count_elements(map, rows, cols, 'P');
    collectible_count = count_elements(map, rows, cols, 'C');
    if (map == NULL || rows <= 0 || cols <= 0) {
        exit_error("Error\nInvalid map or dimensions.");
    }
	check_rectangular_map(map, rows, cols);
	check_map_closed(map, rows, cols);
    check_valid_characters(map, rows, cols);
	if (exit_count != 1 || player_count != 1 || collectible_count < 1)
        exit_error("Error\nMap must contain exactly 1 exit, 1 player, and at least 1 collectible.");
}

void check_rectangular_map(char **map, int rows, int cols)
{
	int i;
	
	i = 0;
	while(i < rows - 1)
	{
        if ((size_t)ft_strlen(map[i]) - 1 != (size_t)cols)
            exit_error("Error\nMap is not rectangular or have an empty line.");		
		i++;
	}
}
