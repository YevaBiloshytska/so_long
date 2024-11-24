/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hey_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:15:50 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/23 00:44:35 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int key_hook(int keycode, t_game *game)
{
    if (keycode == 65307)
        exit_game(game);
    if (keycode == 'w')
        move_player(game, 0, -1);
    else if (keycode == 'a')
        move_player(game, -1, 0);
    else if (keycode == 's')
        move_player(game, 0, 1);
    else if (keycode == 'd')
        move_player(game, 1, 0);

    draw_map(game);
    return 0;
}
