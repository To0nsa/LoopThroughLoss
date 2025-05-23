/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:33:37 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/01 22:37:43 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

int	game_loop(t_game *game)
{
	double	delta_time;

	delta_time = GetFrameTime();
	
	update_music(game, delta_time);
	handle_player_moves(game, delta_time);
	update_transition(game, &game->transition, delta_time);
	update_interaction_block_timer(game, delta_time);
	update_entities_sort(game);
	update_story(game, delta_time);
	update_temp_message(game, delta_time);
	update_voice_timer(game, delta_time);
	update_music(game, delta_time);
	
	BeginDrawing();
	ClearBackground(BLACK);
	handle_events(game);
	draw_background(game);
	render_scene(game, delta_time);
	EndDrawing();
	
	return (0);
}
