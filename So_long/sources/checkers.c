/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:08:13 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/26 16:42:35 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool is_valid(t_game *game, int x, int y)
{
    if (game->map[y][x] == '0' || game->map[y][x] == 'C' ||
        game->map[y][x] == 'P' || game->map[y][x] == 'E') {
        return true;
    }
    return false;
}

void process_neighbors(t_game *game, int x, int y, bool **visited, int queue[][2], int *rear, int directions[4][2]) {
    int i;
	int new_x;
	int new_y;
	
	i = 0;
    while (i < 4) {
        new_x = x + directions[i][0];
        new_y = y + directions[i][1];

        if (!visited[new_y][new_x] && is_valid(game, new_x, new_y)) {
            visited[new_y][new_x] = true;
            queue[*rear][0] = new_x;
            queue[*rear][1] = new_y;
            (*rear)++;
        }
        i++;
    }
}


void bfs(t_game *game, int start_x, int start_y, bool **visited) {
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int queue[game->map_rows * game->map_cols][2];
    int front;
	int rear;
	
	front = 0;
	rear = 0;
	queue[rear][0] = start_x;
    queue[rear][1] = start_y;
    visited[start_y][start_x] = true;
    rear++;

    // Основной цикл
    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        // Обработка соседей
        process_neighbors(game, x, y, visited, queue, &rear, directions);
    }
}

void init_visited(t_game *game, bool ***visited)
{
    *visited = (bool **)malloc(game->map_rows * sizeof(bool *));
    int i;
	int j;

	i = 0;
    while (i < game->map_rows) {
        (*visited)[i] = (bool *)malloc(game->map_cols * sizeof(bool));
        j = 0;
        while (j < game->map_cols) {
            (*visited)[i][j] = false;
            j++;
        }
        i++;
    }
}



void check_items_accessibility(t_game *game, bool **visited)
{
    int i;
	int j;
	
	i = 0;
    while (i < game->map_rows) {
        j = 0;
        while (j < game->map_cols) {
            if ((game->map[i][j] == 'C' || game->map[i][j] == 'E') && !visited[i][j]) {
                printf("Error\nSome items or the exit are not accessible!\n");
                free_visited(game, visited);
                exit(1); // Завершаем игру с ошибкой
            }
            j++;
        }
        i++;
    }
}

void check_accessibility(t_game *game)
{
    bool **visited;
    
    init_visited(game, &visited);
    bfs(game, game->player_x, game->player_y, visited);
    check_items_accessibility(game, visited);
    free_visited(game, visited);
}

