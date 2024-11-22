/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:39:07 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/22 17:04:09 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>

#define FLOOR "textures/floor.xpm"
#define HEART "textures/heart.xpm"
#define EXIT "textures/exit.xpm"
#define PLAYER "textures/player.xpm"
#define WALL "textures/wall.xpm"


// Проверка, доступна ли клетка
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





void exit_error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}


void init_game(t_game *game) {
    game->img_width = 32;
    game->img_height = 32;

    game->MAP_WALL_img = mlx_xpm_file_to_image(game->mlx, WALL, &game->img_width, &game->img_height);
	game->MAP_FLOOR_img = mlx_xpm_file_to_image(game->mlx, FLOOR, &game->img_width, &game->img_height);
	game->MAP_HEART_img = mlx_xpm_file_to_image(game->mlx, HEART, &game->img_width, &game->img_height);
	game->MAP_EXIT_img = mlx_xpm_file_to_image(game->mlx, EXIT, &game->img_width, &game->img_height);
	game->MAP_PLAYER_img = mlx_xpm_file_to_image(game->mlx, PLAYER, &game->img_width, &game->img_height);

	if (!game->MAP_PLAYER_img)
    	exit_error("Failed to load player image.");
	
	game->total_MAP_HEARTs = 0;
	for (int i = 0; i < game->map_rows; i++) {
		for (int j = 0; j < game->map_cols; j++) {
			if (game->map[i][j] == 'C') {
				game->total_MAP_HEARTs++;
			}
		}
	}

	check_accessibility(game);
}

void free_textures(t_game *game) {
    if (game->MAP_WALL_img) mlx_destroy_image(game->mlx, game->MAP_WALL_img);
    if (game->MAP_FLOOR_img) mlx_destroy_image(game->mlx, game->MAP_FLOOR_img);
    if (game->MAP_HEART_img) mlx_destroy_image(game->mlx, game->MAP_HEART_img);
    if (game->MAP_EXIT_img) mlx_destroy_image(game->mlx, game->MAP_EXIT_img);
    if (game->MAP_PLAYER_img) mlx_destroy_image(game->mlx, game->MAP_PLAYER_img);
}

void exit_game(t_game *game) {
    free_map(game->map, game->map_rows); // Очистка карты
    free_textures(game); // Очистка текстур
    mlx_destroy_window(game->mlx, game->win); // Закрытие окна
    mlx_destroy_display(game->mlx); // Уничтожение дисплея
    free(game->mlx); // Освобождение памяти для mlx
    exit(0); // Завершаем игру
}

void close_game(t_game *game)
{
    if (game->mlx) {
        if (game->win)
            mlx_destroy_window(game->mlx, game->win);
        if (game->textures) // Пример для текстур
            free_textures(game);
    }
    free_map(game->map, game->map_rows); // Освобождение карты
}

int close_window(t_game *game)
{
    exit_game(game); // Завершает игру и освобождает ресурсы
    return (0);
}


void free_map(char **map, int rows)
{
    for (int i = 0; i < rows; i++) {
        free(map[i]); // Освобождаем каждую строку карты
    }
    free(map); // Освобождаем сам массив указателей
}

int check_win_condition(t_game *game)
{
    if (game->collected_count == game->total_MAP_HEARTs)
    {
        mlx_string_put(game->mlx, game->win, game->map_cols * TILE_SIZE / 2, game->map_rows * TILE_SIZE / 2, 0xFFFFFF, "You Win!");
        return 1;
    }
    return 0;
}


void move_player(t_game *game, int x_offset, int y_offset)
{
    int new_x = game->player_x + x_offset;
    int new_y = game->player_y + y_offset;

    // Проверка на выход за границы карты
    if (new_x < 0 || new_x >= game->map_cols || new_y < 0 || new_y >= game->map_rows)
        return; // Если новый индекс за пределами карты, не двигаемся

    char target_cell = game->map[new_y][new_x];

    // Проверка на стену
    if (target_cell == '1')
        return;

    // Проверка на выход (E), если не собраны все предметы
if (target_cell == 'E') {
    // Если не собраны все предметы, не пускаем игрока на выход
    if (game->collected_count < game->total_MAP_HEARTs) {
        return; // Не пускаем на выход
    }

    // Если все предметы собраны и игрок стоит на выходе
    printf("You win! Exiting the game...\n");
    exit_game(game); // Завершаем игру
}



    // Если на клетке коллекционный предмет
    if (target_cell == 'C') {
        game->collected_count++; // Увеличиваем счетчик собранных предметов
    }

    // Обновление карты: убираем игрока с предыдущей позиции
    game->map[game->player_y][game->player_x] = '0';

    // Устанавливаем игрока на новой позиции
    game->map[new_y][new_x] = 'P';

    // Обновляем координаты игрока
    game->player_x = new_x;
    game->player_y = new_y;

    // Увеличиваем счётчик движений
    game->move_count++;
    printf("Moves: %d\n", game->move_count);

    // Если игрок достиг выхода и собрал все предметы
    // Эта проверка теперь внутри блока выше
}










