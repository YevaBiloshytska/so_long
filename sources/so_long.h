/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:30:51 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/12/05 21:12:43 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <mlx.h>
# include "../libraries/Libft/libft.h"
# include "../libraries/Get_next_line/get_next_line.h"
# include "../libraries/ft_printf/ft_printf.h"
# include <fcntl.h>
# include <string.h>

# define SIZE	32

# define FLOOR "textures/floor.xpm"
# define HEART "textures/heart.xpm"
# define EXIT "textures/exit.xpm"
# define PLAYER "textures/player.xpm"
# define WALL "textures/wall.xpm"
# define EXSPR "textures/exit_sprite.xpm"

typedef struct s_game
{
	int		player_x;
	int		player_y;
	int		x;
	int		y;
	int		new_x;
	int		new_y;
	int		collected_count;
	int		total_collectibles;
	int		map_rows;
	int		map_cols;
	int		move_count;
	int		total_hearts;
	int		fd;
	int		*queue;

	char	**map;

	void	*mlx;
	void	*win;
	void	*wall_img;
	void	*floor_img;
	void	*heart_img;
	void	*exit_img;
	void	*player_img;
	void	*exspr_img;

	bool	**visited;
}	t_game;

int		close_window(t_game *game);
int		key_hook(int keycode, t_game *game);
int		count_elements(t_game *game, char element);
int		open_and_validate_file(t_game *game, const char *filename);
void	init_game(t_game *game);
void	exit_game(t_game *game, const char *msg);
void	move_player(t_game *game, int x_offset, int y_offset);
void	draw_map(t_game *game);
void	load_map(const char *filename, t_game *game);
void	validate_map(t_game *game);
void	free_textures(t_game *game);
void	free_map(char **map, int rows);
void	check_map_closed(t_game *game);
void	check_valid_characters(t_game *game);
void	check_accessibility(t_game *game);
void	check_rectangular_map(t_game *game);
void	free_visited(t_game *game);
void	init_visited(t_game *game);
void	check_path_to(t_game *game, int *front, int *rear, char target);
void	count(t_game *game);
void	check_map_size(t_game *game);
void	bfs(t_game *game, void (*check_path_to)(t_game *game,
				int *front, int *rear, char target), char target);
#endif
