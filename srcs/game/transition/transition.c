/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:33:20 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 00:45:26 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	init_transition(t_game *game, t_transition *transition, double duration)
{
	game->fade_img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->fade_img.addr = mlx_get_data_addr(game->fade_img.ptr,
											&game->fade_img.bpp,
											&game->fade_img.line_size,
											&game->fade_img.endian);
	transition->duration = duration;
	transition->fade_alpha = 0.0;
	transition->timer = 0.0;
	transition->state = FADE_IDLE;
}

void	start_fade_out(t_transition *transition)
{
	transition->state = FADE_OUT;
	transition->timer = 0.0;
}

void	start_fade_in(t_transition *transition)
{
	transition->state = FADE_IN;
	transition->timer = 0.0;
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
			start_fade_in(transition);
		}
		else
			transition->state = FADE_IDLE;
	}

	if (transition->state == FADE_OUT)
		transition->fade_alpha = transition->timer / transition->duration;
	else if (transition->state == FADE_IN)
		transition->fade_alpha = 1.0 - (transition->timer / transition->duration);
}

void	fill_transition_image(t_game *game, t_transition *transition)
{
	int				x, y;
	t_img			*fade_img = &game->fade_img;
	t_img			*scene_img = &game->img;
	unsigned int	*fade_ptr;
	unsigned int	*scene_ptr;
	unsigned char	r, g, b;
	double			alpha = transition->fade_alpha;

	if (!fade_img->addr || !scene_img->addr)
		return ;

	for (y = 0; y < WIN_H; y++)
	{
		for (x = 0; x < WIN_W; x++)
		{
			int offset = y * fade_img->line_size + x * (fade_img->bpp / 8);

			scene_ptr = (unsigned int *)(scene_img->addr + offset);
			fade_ptr = (unsigned int *)(fade_img->addr + offset);

			if (!scene_ptr || !fade_ptr)
				continue;

			unsigned int scene_color = *scene_ptr;

			r = ((scene_color >> 16) & 0xFF) * (1.0 - alpha);
			g = ((scene_color >> 8) & 0xFF) * (1.0 - alpha);
			b = (scene_color & 0xFF) * (1.0 - alpha);

			*fade_ptr = (r << 16) | (g << 8) | b;
		}
	}
}

void render_transition(t_game *game, t_transition *transition)
{
    if (transition->state == FADE_IDLE && transition->fade_alpha <= 0.01)
        return;

    fill_transition_image(game, transition);
    mlx_put_image_to_window(game->mlx, game->window->ptr, game->fade_img.ptr, 0, 0);
}
