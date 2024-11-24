/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:08:13 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/22 21:04:40 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool is_valid(t_game *game, int x, int y)
{
    // Вместо strcmp, просто сравниваем символы
    if (game->map[y][x] == '0' || game->map[y][x] == 'C' ||
        game->map[y][x] == 'P' || game->map[y][x] == 'E') {
        return true;
    }
    return false;
}

// BFS для поиска всех доступных клеток
void bfs(t_game *game, int start_x, int start_y, bool **visited) 
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Направления (влево, вправо, вверх, вниз)
    int queue[game->map_rows * game->map_cols][2]; // Очередь для BFS
    int front = 0, rear = 0;

    queue[rear][0] = start_x;
    queue[rear][1] = start_y;
    visited[start_y][start_x] = true;
    rear++;

    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        // Проверяем все соседние клетки
        for (int i = 0; i < 4; i++) {
            int new_x = x + directions[i][0];
            int new_y = y + directions[i][1];

            // Проверка на выход за границы и на посещенность клетки
            if (new_x >= 0 && new_x < game->map_cols && new_y >= 0 && new_y < game->map_rows && !visited[new_y][new_x] && is_valid(game, new_x, new_y)) {
                visited[new_y][new_x] = true;
                queue[rear][0] = new_x;
                queue[rear][1] = new_y;
                rear++;
            }
        }
    }
}

// Проверка доступности всех предметов и выхода
void check_accessibility(t_game *game)
{
    bool **visited = (bool **)malloc(game->map_rows * sizeof(bool *));
    for (int i = 0; i < game->map_rows; i++) {
        visited[i] = (bool *)malloc(game->map_cols * sizeof(bool));
        for (int j = 0; j < game->map_cols; j++) {
            visited[i][j] = false;
        }
    }

    // Начинаем BFS с позиции игрока
    bfs(game, game->player_x, game->player_y, visited);

    // Проверяем доступность всех коллекционных предметов и выхода
    for (int i = 0; i < game->map_rows; i++) {
        for (int j = 0; j < game->map_cols; j++) {
            // Просто сравниваем символы
            if ((game->map[i][j] == 'C' || game->map[i][j] == 'E') && !visited[i][j]) {
                printf("Error\nSome items or the exit are not accessible!\n");
                for (int i = 0; i < game->map_rows; i++) {
                    free(visited[i]);
                }
                free(visited);
                exit(1); // Завершаем игру с ошибкой
            }
        }
    }

    // Если все предметы и выход доступны, продолжаем игру

    for (int i = 0; i < game->map_rows; i++) {
        free(visited[i]);
    }
    free(visited);
}
