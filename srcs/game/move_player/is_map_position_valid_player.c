/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_position_valid_player.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:13:27 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 22:58:39 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static bool	is_within_bounds(t_game *game, t_point pos)
{
	return (pos.x >= 0 && pos.x < game->map->size.x
		&& pos.y >= 0 && pos.y < game->map->size.y);
}

static bool	is_wall(t_game *game, t_point pos)
{
	return (game->map->matrix[(int)(pos.y)][(int)pos.x] == WALL
			|| game->map->matrix[(int)(pos.y)][(int)pos.x] == DOOR);
}

static bool	is_blocked(t_game *game, t_dpoint pos)
{
	t_point	grid_pos;

	grid_pos = (t_point){(int)pos.x, (int)pos.y};
	return (!is_within_bounds(game, grid_pos) || is_wall(game, grid_pos));
}

bool	is_map_position_valid_player(t_game *game, t_dpoint pos)
{
	t_dpoint	checks[4];
	int			i;

	if (is_blocked(game, pos))
		return (false);
	checks[0] = (t_dpoint){pos.x - 1.0, pos.y};
	checks[1] = (t_dpoint){pos.x + 1.0, pos.y};
	checks[2] = (t_dpoint){pos.x, pos.y - 1.0};
	checks[3] = (t_dpoint){pos.x, pos.y + 1.0};
	i = 0;
	while (i < 4)
	{
		if (is_blocked(game, checks[i]))
			return (false);
		i++;
	}
	return (true);
}
