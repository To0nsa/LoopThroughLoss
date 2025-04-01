/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/01 16:26:57 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	render_scene(t_game *game, double delta_time)
{
	t_ray	ray;
	double	*z_buffer = x_calloc(game, WIN_W, sizeof(double));

	(void)delta_time;
	for (int x = 0; x < WIN_W; x++)
		raycast(game, &ray, x, z_buffer);

	draw_entities(game, z_buffer);

	draw_npc_dialogue(game);
	draw_temp_message(game);

	render_transition(game, &game->transition);

	if (game->story.state == ACCEPTANCE_LOOP
		&& game->story.has_interacted_with_door)
	{
		Color gold = (Color){ 255, 215, 0, 255 };
		Color white = (Color){ 255, 255, 255, 255 };

		int	cover_height = (int)(WIN_H * game->story.cover_progress);

		DrawRectangleGradientV
			(0, WIN_H - cover_height, WIN_W, cover_height, gold, white);
		if (game->story.cover_progress > 0.6f)
		{
			int x = (WIN_W >> 1) - 350;
			int y = WIN_H - (WIN_H / 5);
			DrawTextEx(game->font.dialogue,
				"Acceptance is never an easy journey, her absence echoes in each moment.",
				(Vector2){x, y - 30}, 24, 1.0f, BLACK);
			DrawTextEx(game->font.dialogue,
				"Though she's gone, you carry her, and the mark she made on this world, with you.",
				(Vector2){x, y}, 24, 1.0f, BLACK);
			DrawTextEx(game->font.dialogue,
				"to my mother",
				(Vector2){x + (WIN_W / 2), y + 60}, 24, 1.0f, BLACK);
		}
	}

	free(z_buffer);
}
