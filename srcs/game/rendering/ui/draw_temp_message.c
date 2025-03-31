/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_temp_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:35:20 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 11:57:41 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	update_temp_message(t_game *game, double delta_time)
{
	if (game->temp_msg_visible)
	{
		game->temp_msg_timer -= delta_time;
		if (game->temp_msg_timer <= 0)
		{
			game->temp_msg_visible = false;
			game->temp_msg[0] = '\0';
		}
	}
}

void	show_temp_message(t_game *game, double duration, const char *message)
{
	ft_strlcpy(game->temp_msg, message, sizeof(game->temp_msg));
	game->temp_msg_visible = true;
	game->temp_msg_timer = duration;
	game->temp_msg_timer_max = duration;
}

void	draw_temp_message(t_game *game)
{
	if (!game->temp_msg_visible)
		return;

	int x = (WIN_W >> 1) - 300;
	int y = WIN_H - (WIN_H / 5);
	int w = 600;
	int h = 80;

	float fade_duration = 0.3f;
	float alpha = 1.0f;

	// Calcul alpha pour fade-in / fade-out
	if (game->temp_msg_timer < fade_duration)
		alpha = game->temp_msg_timer / fade_duration;
	else if (game->temp_msg_timer > game->temp_msg_timer_max - fade_duration)
		alpha = (game->temp_msg_timer_max - game->temp_msg_timer) / fade_duration;

	alpha = Clamp(alpha, 0.0f, 1.0f); // sécurité

	Color box_color = Fade(DARKGRAY, 0.6f * alpha);
	Color border_color = Fade(GRAY, alpha);
	Color text_color = Fade(WHITE, alpha);

	// Bordure simulée
	DrawRectangleRounded((Rectangle){x - 2, y - 2, w + 4, h + 4}, 0.2f, 16, border_color);

	// Boîte principale
	DrawRectangleRounded((Rectangle){x, y, w, h}, 0.2f, 16, box_color);

	// Texte
	DrawTextEx(game->font.interaction, game->temp_msg, (Vector2){x + 20, y + 30}, 24, 1.0f, text_color);
}

