/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_npc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:06:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 15:01:36 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

/* static bool	is_player_near_npc(t_npc *npc, t_player *player, double range)
{
	return (ft_cab_dist_dpoint(player->pos, npc->pos) < range);
} */

/* static void	reset_animations(t_npc *npc)
{
	npc->sprite.anim_index = 0;
	npc->sprite.anim_timer = 0.0;
} */

/* static void	update_npc_state(t_npc *npc, t_player *player)
{
	t_npc_state	previous_state;

	previous_state = npc->state;
	if (npc->state == SPEAK)
		return ;
	if (is_player_near_npc(npc, player, 2.0))
		npc->state = IDLE;
	if (npc->state != previous_state)
		reset_animations_and_path(npc);
} */

/* void	update_npc(t_game *game, t_npc *npc, double delta_time)
{
	update_npc_state(npc, &game->player);
	if (npc->state == SPEAK)
		play_speak_animation(npc, delta_time);
	else if (npc->state == IDLE)
		play_wait_animation(npc, delta_time);

} */
