/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:37:04 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/24 20:12:15 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void load_map(const char *filename, t_game *game)
{
    char *line;
    int map_rows = 0;
    int map_cols = 0;
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit_error("Error\nFailed to open map file.");

    game->map = NULL; // Инициализируем карту
    game->total_collectibles = 0; // Инициализируем количество коллекционных предметов
	line = get_next_line(fd);
    while (line != NULL)
    {
        if (map_cols == 0)
            map_cols = ft_strlen(line) - 1; // Устанавливаем количество колонок

        // Расширяем массив строк
        game->map = realloc(game->map, (map_rows + 1) * sizeof(char *));
        if (!game->map)
        {
            free(line);
            close(fd);
            exit_error("Error\nMemory allocation failed.");
        }

        // Сохраняем текущую строку
        game->map[map_rows] = line;

        // Подсчёт коллекционных предметов ('C') в текущей строке
        for (int j = 0; j < map_cols; j++)
        {
            if (line[j] == 'C')
                game->total_collectibles++;
        }

        map_rows++;
    }

    close(fd);

    if (map_rows == 0 || map_cols == 0)
        exit_error("Error\nMap is empty or invalid.");

    game->map_rows = map_rows;
    game->map_cols = map_cols;

    // Находим позицию игрока ('P')
    for (int i = 0; i < map_rows; i++)
    {
        for (int j = 0; j < map_cols; j++)
        {
            if (game->map[i][j] == 'P')
            {
                game->player_x = j;
                game->player_y = i;
                break;
            }
        }
    }
}

void	check_map_closed(char **map, int rows, int cols)
{
    int i;

    for (i = 0; i < cols; i++)
    {
        if (map[0][i] != '1' || map[rows - 1][i] != '1')
            exit_error("Error\nMap is not surrounded by walls.");
    }

    for (i = 0; i < rows; i++)
    {
        if (map[i][0] != '1' || map[i][cols - 1] != '1')
            exit_error("Error\nMap is not surrounded by walls.");
    }
}

//проверяет, содержит ли карта только допустимые символы.
void check_valid_characters(char **map, int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'C' && map[i][j] != 'E' && map[i][j] != 'P')
                exit_error("Error\nInvalid character in map.");
        }
    }
}

int count_elements(char **map, int rows, int cols, char element)
{
    int count = 0;

    // Проверка на корректность доступа к карте
    if (map == NULL || rows <= 0 || cols <= 0) {
        exit_error("Error\nInvalid map or dimensions.");
    }

    for (int i = 0; i < rows; i++) {
        if (map[i] == NULL) {
            exit_error("Error\nInvalid row in map.");
        }
        
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == element) {
                count++;
            }
        }
    }

    return count;
}

void validate_map(char **map, int rows, int cols)
{
    if (map == NULL || rows <= 0 || cols <= 0) {
        exit_error("Error\nInvalid map or dimensions.");
    }

    int exit_count = count_elements(map, rows, cols, 'E');
    int player_count = count_elements(map, rows, cols, 'P');
    int collectible_count = count_elements(map, rows, cols, 'C');

	check_rectangular_map(map, rows, cols);  // Проверка, что карта прямоугольная
	check_map_closed(map, rows, cols);  // Проверка, что карта окружена стенами
    check_valid_characters(map, rows, cols);  // Проверка допустимых символов
    if (exit_count != 1 || player_count != 1 || collectible_count < 1) {
        exit_error("Error\nMap must contain exactly 1 exit, 1 player, and at least 1 collectible.");
    }
}

void check_rectangular_map(char **map, int rows, int cols)
{
    for (int i = 0; i < rows - 1; i++) {
        if (map[i] == NULL || (size_t)ft_strlen(map[i]) - 1 != (size_t)cols) {
            exit_error("Error\nMap is not rectangular or have an empty line.");
        }
    }
}
