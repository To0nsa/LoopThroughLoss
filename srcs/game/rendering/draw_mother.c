/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:32:30 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 15:19:27 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static void	setup_temp_sprite(t_sprite *temp, t_npc *npc, t_texture *tex)
{
	ft_memset(temp, 0, sizeof(t_sprite));
	temp->pos = npc->pos;
	temp->size = npc->sprite.size;
	temp->idle_frames_count = 1;
	temp->idle_frames = tex;
}

void	draw_mother(t_game *game, t_npc *npc, double *z_buffer)
{
	t_sprite	temp;

	setup_temp_sprite(&temp, npc, &npc->texture);
	draw_sprite(game, game->player, &temp, z_buffer);
}
