/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:30:51 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/22 17:01:11 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdbool.h>
# include <mlx.h>
# include "../libraries/Libft/libft.h"
# include "../libraries/get_next_line/get_next_line.h"
# include <fcntl.h>
# include <string.h>

#define TILE_SIZE           32


# define TEXTURE_WALL      "textures/wall.xpm"  // Путь к текстуре стены
# define TEXTURE_FLOOR     "textures/floor.xpm" // Путь к текстуре пола
# define TEXTURE_HEART     "textures/heart.xpm" // Путь к текстуре сердца
# define TEXTURE_PLAYER    "textures/player.xpm" // Путь к текстуре игрока
# define TEXTURE_EXIT      "textures/exit.xpm"  // Путь к текстуре выхода




typedef struct s_game {
    void    *mlx;               // Указатель на инициализацию MiniLibX
    void    *win;               // Указатель на окно игры
    char    **map;              // Двумерный массив карты
    int     player_x;           // Координата X игрока на карте
    int     player_y;           // Координата Y игрока на карте
    int     collected_count;    // Количество собранных предметов
    int     total_collectibles; // Общее количество предметов для сбора
    int     map_rows;           // Количество строк карты
    int     map_cols;           // Количество столбцов карты
    int     img_width;          // Добавить переменную для ширины
    int     img_height;         // Добавить переменную для высоты
	int     move_count; 
	
	void    **textures;			// Массив текстур (например, для стен, пола и т.д.)
    void    *MAP_WALL_img;          // Изображение стены
    void    *MAP_FLOOR_img;         // Изображение пола
    void    *MAP_HEART_img;   // Изображение предмета
    void    *MAP_EXIT_img;          // Изображение выхода
    void    *MAP_PLAYER_img;        // Изображение игрока
	bool is_valid;
	int total_MAP_HEARTs; // Общее количество "сердечек"
	
} t_game;

void init_game(t_game *game);
void exit_game(t_game *game);
void close_game(t_game *game);
void move_player(t_game *game, int x_offset, int y_offset);
void draw_map(t_game *game);
void load_map(const char *filename, t_game *game);
void validate_map(char **map, int rows, int cols);
int  check_win_condition(t_game *game);
void free_textures(t_game *game);
void free_map(char **map, int rows);
int key_hook(int keycode, t_game *game);
void	check_map_closed(char **map, int rows, int cols);
void check_valid_characters(char **map, int rows, int cols);
int count_elements(char **map, int rows, int cols, char element);
bool is_valid(t_game *game, int x, int y);
void bfs(t_game *game, int start_x, int start_y, bool **visited);
void check_accessibility(t_game *game);
void exit_error(const char *msg);
int close_window(t_game *game);
#endif
