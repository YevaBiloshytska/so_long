/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <nikolly19.12@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:30:51 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/13 21:28:41 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include "../libraries/Libft/libft.h"
# include "../libraries/Get_next_line/get_next_line.h"

# include <fcntl.h>
# include <string.h>

#define TILE_SIZE           32

# define WALL			"textures/wall.xpm" //Путь к изображению стены
# define FLOOR			"textures/floor.xpm" //Путь к изображению пола
# define HEART			"textures/heart.xpm" //Путь к изображению монет
# define PLAYER     	"textures/player.xpm" //Путь к изображению игрока
# define EXIT       	"textures/exit.xpm" //Путь к изображению закрытого выхода



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

    void    *wall_img;          // Изображение стены
    void    *empty_img;         // Изображение пола
    void    *collectible_img;   // Изображение предмета
    void    *exit_img;          // Изображение выхода
    void    *player_img;        // Изображение игрока
} t_game;

void init_game(t_game *game);
void exit_error(const char *msg);
void exit_game(t_game *game);
void close_game(t_game *game);
void move_player(t_game *game, int x_offset, int y_offset);
void draw_map(t_game *game);
void load_map(const char *filename, t_game *game);
void validate_map(char **map, int rows, int cols);
int  check_win_condition(t_game *game);
void free_textures(t_game *game);
void free_map(char **map);
int key_hook(int keycode, t_game *game);
void	check_map_closed(char **map, int rows, int cols);
void check_valid_characters(char **map, int rows, int cols);
int count_elements(char **map, char element);

#endif
