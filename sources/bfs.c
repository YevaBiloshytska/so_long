/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:39:29 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/12/05 21:23:26 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_directions(int directions[4][2])
{
	directions[0][0] = -1;
	directions[0][1] = 0;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = 0;
	directions[3][1] = 1;
}

void	check_path_to(t_game *game, int *front, int *rear, char target)
{
	int	directions[4][2];
	int	i;

	init_directions(directions);
	while (*front < *rear)
	{
		i = -1;
		game->x = game->queue[*front * 2];
		game->y = game->queue[*front * 2 + 1];
		(*front)++;
		while (++i < 4)
		{
			game->new_x = game->x + directions[i][0];
			game->new_y = game->y + directions[i][1];
			if (!game->visited[game->new_y][game->new_x] && (game->map \
			[game->new_y][game->new_x] == '0' || game->map \
			[game->new_y][game->new_x] == 'C' || game->map \
			[game->new_y][game->new_x] == target))
			{
				game->visited[game->new_y][game->new_x] = true;
				game->queue[*rear * 2] = game->new_x;
				game->queue [((*rear)++) * 2 + 1] = game->new_y;
			}
		}
	}
}

void	bfs(t_game *game, void (*check_path_to)(t_game *game,
	int	*front, int *rear, char target), char target)
{
	int	front;
	int	rear;
	int	queue_size;

	if (game->map_rows <= 0 || game->map_cols <= 0)
		exit_game(game, "Error\nInvalid map dimensions.");
	queue_size = game->map_rows * game->map_cols * 2;
	if (queue_size <= 0)
		exit_game(game, "Error\nQueue size is invalid.");
	game->queue = (int *)malloc(queue_size * sizeof(int));
	if (!game->queue)
	{
		exit_game (game, "Error\nFailed to allocate memory for queue.");
	}
	game->x = game->player_x;
	game->y = game->player_y;
	front = 0;
	rear = 0;
	game->queue[rear * 2] = game->x;
	game->queue[rear * 2 + 1] = game->y;
	game->visited[game->y][game->x] = true;
	rear++;
	check_path_to(game, &front, &rear, target);
	free(game->queue);
}

void	init_visited(t_game *game)
{
	int	i;
	int	j;

	game->visited = (bool **)malloc(game->map_rows * sizeof(bool *));
	if (!game->visited)
		exit_game(game, "Error\nFailed to allocate memory for visited array.");
	i = 0;
	while (i < game->map_rows)
	{
		game->visited[i] = (bool *)malloc(game->map_cols * sizeof(bool));
		if (!game->visited[i])
		{
			free(game->visited);
			exit_game(game, "Error\nFailed to allocate"
				"memory for visited row.");
		}
		j = 0;
		while (j < game->map_cols)
		{
			game->visited[i][j] = false;
			j++;
		}
		i++;
	}
}
