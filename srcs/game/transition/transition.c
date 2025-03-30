/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:33:20 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 15:40:37 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	init_transition(t_game *game, t_transition *transition, double duration)
{
	(void)game;
	transition->duration = duration;
	transition->fade_alpha = 0.0;
	transition->timer = 0.0;
	transition->state = FADE_IDLE;
	transition->on = false;
}

void	start_fade_out(t_transition *transition)
{
	transition->state = FADE_OUT;
	transition->timer = 0.0;
	transition->on = true;
}

void	start_fade_in(t_transition *transition)
{
	transition->state = FADE_IN;
	transition->timer = 0.0;
	transition->on = true;
}

void	update_transition(t_game *game, t_transition *transition, double delta_time)
{
	if (transition->state == FADE_IDLE)
		return;

	transition->timer += delta_time;
	if (transition->timer >= transition->duration)
	{
		transition->timer = transition->duration;

		if (transition->state == FADE_OUT)
		{
			reset_player(game, &game->player);
			game->story.has_interacted_with_door = false;
			game->story.has_spoken_to_mother = false;
			start_fade_in(transition);
		}
		else
		{
			transition->state = FADE_IDLE;
			transition->on = false;
		}
	}

	if (transition->state == FADE_OUT)
		transition->fade_alpha = transition->timer / transition->duration;
	else if (transition->state == FADE_IN)
		transition->fade_alpha = 1.0 - (transition->timer / transition->duration);
}

void	render_transition(t_game *game, t_transition *transition)
{
	(void)game;
	if (transition->state == FADE_IDLE && transition->fade_alpha <= 0.01)
		return ;

	Color fade_color = Fade(BLACK, transition->fade_alpha);
	DrawRectangle(0, 0, WIN_W, WIN_H, fade_color);
}
