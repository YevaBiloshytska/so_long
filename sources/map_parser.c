/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:37:04 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/21 15:23:07 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_map(const char *filename, t_game *game)
{
    FILE *fd;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int map_rows = 0;
    int map_cols = 0;

    fd = fopen(filename, "r");  // Открываем файл карты
    if (fd == NULL)
        exit_error("Error\nFailed to open map file.");

    game->map = NULL;  // Инициализируем карту
    game->total_collectibles = 0; // Инициализируем количество предметов

    while ((read = getline(&line, &len, fd)) != -1) 
    {
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (map_cols == 0)  // Устанавливаем количество колонок
            map_cols = strlen(line);

        // Проверка на realloc
        char **new_map = realloc(game->map, (map_rows + 1) * sizeof(char *));
        if (new_map == NULL)
        {
            free(game->map);  // Освобождаем старую память, если realloc не удался
            exit_error("Error\nMemory allocation failed for map rows.");
        }
        game->map = new_map;  // Присваиваем новую память

        game->map[map_rows] = line;
        map_rows++;

        // Подсчёт коллекционных предметов ('C') в текущей строке
        for (int j = 0; j < map_cols; j++) {
            if (line[j] == 'C') {
                game->total_collectibles++;
            }
        }

        line = NULL;  // Обнуляем line для следующей строки
    }

    fclose(fd);

    if (map_rows == 0 || map_cols == 0)
        exit_error("Error\nMap is empty or invalid.");

    validate_map(game->map, map_rows, map_cols);

    game->map_rows = map_rows;
    game->map_cols = map_cols;

    // Найдем позицию игрока ('P')
    for (int i = 0; i < map_rows; i++) {
        for (int j = 0; j < map_cols; j++) {
            if (game->map[i][j] == 'P') {
                game->player_x = j;  // Устанавливаем координаты игрока по оси X
                game->player_y = i;  // Устанавливаем координаты игрока по оси Y
                break;
            }
        }
    }

    free(line);
}




void	check_map_closed(char **map, int rows, int cols)
{
    int i;

    // Проверка верхней и нижней границ
    for (i = 0; i < cols; i++)
    {
        if (map[0][i] != '1' || map[rows - 1][i] != '1')
            exit_error("Error\nMap is not surrounded by walls.");
    }

    // Проверка левых и правых границ
    for (i = 0; i < rows; i++)
    {
        if (map[i][0] != '1' || map[i][cols - 1] != '1')
            exit_error("Error\nMap is not surrounded by walls.");
    }
}

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
    // Проверка на корректность карты и её размеров
    if (map == NULL || rows <= 0 || cols <= 0) {
        exit_error("Error\nInvalid map or dimensions.");
    }

    int exit_count = count_elements(map, rows, cols, 'E');
    int player_count = count_elements(map, rows, cols, 'P');
    int collectible_count = count_elements(map, rows, cols, 'C');

    if (exit_count != 1 || player_count != 1 || collectible_count < 1) {
        exit_error("Error\nMap must contain exactly 1 exit, 1 player, and at least 1 collectible.");
    }
    
    check_map_closed(map, rows, cols);
    check_valid_characters(map, rows, cols);
}
