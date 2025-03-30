/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:36:54 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 22:57:39 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

bool	is_facing_target(t_player *player, t_dpoint target_pos)
{
	t_dpoint	target_dir;
	double		dot;
	double		fov_threshold;

	target_dir = get_unit_direction_vector(player->pos, target_pos);
	dot = get_dot_product(player->facing_dir, target_dir);
	fov_threshold = FOV_THRESHOLD;
	return (dot >= fov_threshold);
}

void	block_interactions_for_seconds(t_game *game, double seconds)
{
	game->interactions_blocked = true;
	game->interaction_block_timer = seconds;
}

void	update_interaction_block_timer(t_game *game, double delta_time)
{
	if (game->interactions_blocked)
	{
		game->interaction_block_timer -= delta_time;
		if (game->interaction_block_timer <= 0)
		{
			game->interactions_blocked = false;
			game->interaction_block_timer = 0;
		}
	}
}
