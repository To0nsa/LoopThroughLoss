/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 23:04:22 by nlouis           ###   ########.fr       */
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

	free(z_buffer);
}
