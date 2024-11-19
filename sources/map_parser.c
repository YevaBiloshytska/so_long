/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <nikolly19.12@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:37:04 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/13 22:35:54 by ybiloshy         ###   ########.fr       */
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
        exit_error("Failed to open map file.");

    // Инициализируем карту (пока пустой массив)
    game->map = NULL;

    // Считываем строки карты с использованием fgets
    while ((read = getline(&line, &len, fd)) != -1) 
    {
        // Убираем символ новой строки, если он есть
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (map_cols == 0)  // Устанавливаем количество колонок (ширину карты)
            map_cols = strlen(line);  // Длина строки без символа новой строки

        // Расширяем массив указателей на строки
        game->map = realloc(game->map, (map_rows + 1) * sizeof(char *));
        if (game->map == NULL)
            exit_error("Memory allocation failed for map rows.");
        
        game->map[map_rows] = line;  // Сохраняем строку карты
        map_rows++;
        
        line = NULL;  // Для того чтобы getline выделила новый буфер на следующую строку
    }

    fclose(fd);  // Закрываем файл

    // Проверка на пустую карту
    if (map_rows == 0 || map_cols == 0)
        exit_error("Map is empty or invalid.");

    // Проверка, что карта замкнута и содержит правильные символы
    validate_map(game->map, map_rows, map_cols);

    game->map_rows = map_rows;
    game->map_cols = map_cols;

    // Не забываем освободить память, выделенную для строки после использования
    free(line);
}

void	check_map_closed(char **map, int rows, int cols)
{
    int i;

    // Проверка верхней и нижней границ
    for (i = 0; i < cols; i++)
    {
        if (map[0][i] != '1' || map[rows - 1][i] != '1')
            exit_error("Map is not surrounded by walls.");
    }

    // Проверка левых и правых границ
    for (i = 0; i < rows; i++)
    {
        if (map[i][0] != '1' || map[i][cols - 1] != '1')
            exit_error("Map is not surrounded by walls.");
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
                exit_error("Invalid character in map.");
        }
    }
}

int count_elements(char **map, char element)
{
    int i, j;
    int count = 0;

    for (i = 0; map[i]; i++)
    {
        for (j = 0; map[i][j]; j++)
        {
            if (map[i][j] == element)
                count++;
        }
    }
    return count;
}

void validate_map(char **map, int rows, int cols)
{
    int exit_count = count_elements(map, 'E');
    int player_count = count_elements(map, 'P');
    int collectible_count = count_elements(map, 'C');

    if (exit_count != 1 || player_count != 1 || collectible_count < 1)
        exit_error("Map must contain exactly 1 exit, 1 player, and at least 1 collectible.");
    
    check_map_closed(map, rows, cols);
    check_valid_characters(map, rows, cols);
}
