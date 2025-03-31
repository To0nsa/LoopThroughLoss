/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:46:10 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 20:48:54 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	update_door_list(t_game *game, t_door *door)
{
	game->doors = x_realloc(game, game->doors,
			game->door_count * sizeof(t_door *),
			(game->door_count + 1) * sizeof(t_door *));
	game->doors[game->door_count] = door;
	game->door_count++;
}

void	spawn_door(t_game *game, double x, double y)
{
	t_door		*door;

	door = x_calloc(game, 1, sizeof(t_door));
	door->name = "door";
	door->pos = (t_dpoint){x, y};
	door->type = DOOR_T;
	door->state = CLOSED;
	update_door_list(game, door);
}

void	spawn_frame(t_game *game, double x, double y)
{
	t_door		*door;

	door = x_calloc(game, 1, sizeof(t_door));
	door->name = "frame";
	door->pos = (t_dpoint){x, y};
	door->type = FRAME_T;
	door->state = CLOSED;
	update_door_list(game, door);
}
