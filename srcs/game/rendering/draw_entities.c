/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:34:03 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 15:35:49 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static void	draw_npc(t_game *game, t_npc *npc, double *z_buffer)
{
	if (ft_strcmp(npc->type, "mother") == 0)
		draw_mother(game, npc, z_buffer);
}

static void	draw_item(t_game *game, t_item *item, double *z_buffer)
{
	draw_texture(game, &item->texture, item->pos, z_buffer);
}

void	draw_entities(t_game *game, double *z_buffer)
{
	int	i;

	i = -1;
	while (++i < game->entity_count)
	{
		if (game->entities[i].type == NPC)
			draw_npc(game, (t_npc *)game->entities[i].ptr, z_buffer);
		else if (game->entities[i].type == ITEM)
			draw_item(game, (t_item *)game->entities[i].ptr, z_buffer);
	}
}
