/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:38:34 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 13:46:29 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static void	set_player_facing_angle(t_player *player)
{
	if (player->conf_dir == 'N')
		player->facing_angle = 3 * M_PI / 2;
	else if (player->conf_dir == 'S')
		player->facing_angle = M_PI / 2;
	else if (player->conf_dir == 'W')
		player->facing_angle = M_PI;
	else if (player->conf_dir == 'E')
		player->facing_angle = 0;
}

static void	set_player_direction_and_view_plane(t_player *player)
{
	player->facing_dir.x = cos(player->facing_angle);
	player->facing_dir.y = sin(player->facing_angle);
	player->view_plane.x = -sin(player->facing_angle) * FOV;
	player->view_plane.y = cos(player->facing_angle) * FOV;
}

void	init_player(t_game *game, t_player *player)
{
	(void)game;
	player->pos.x += 0.5;
	player->pos.y += 0.5;
	player->start_pos = player->pos;
	player->rot_speed = 3;
	player->move_speed = 1;
	set_player_facing_angle(player);
	player->start_facing_angle = player->facing_angle;
	set_player_direction_and_view_plane(player);
}

void	reset_player(t_game *game, t_player *player)
{
	(void)game;
	player->pos = player->start_pos;
	player->facing_angle = player->start_facing_angle;
	set_player_direction_and_view_plane(player);
}
