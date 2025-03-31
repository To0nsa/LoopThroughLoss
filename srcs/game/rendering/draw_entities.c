/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:34:03 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 12:16:21 by nlouis           ###   ########.fr       */
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

static void	draw_mother(t_game *game, t_npc *npc, double *z_buffer)
{
	t_sprite	temp;

	if (npc->state == NOT_PRESENT)
		return ;
	if (npc->is_blurry)
		setup_temp_sprite(&temp, npc, &npc->texture_blurry);
	else
		setup_temp_sprite(&temp, npc, &npc->texture_idle);
	draw_sprite(game, game->player, &temp, z_buffer);
}

static void	draw_npc(t_game *game, t_npc *npc, double *z_buffer)
{
	if (ft_strcmp(npc->type, "mother") == 0)
		draw_mother(game, npc, z_buffer);
}

static void	draw_item(t_game *game, t_item *item, double *z_buffer)
{
	if (ft_strcmp(item->name, "answering_machine") == 0)
	{
		if (item->is_broken)
			draw_texture(game, &item->texture_broken, item->pos, z_buffer);
		else if (item->has_message)
			draw_texture(game, &item->texture_message, item->pos, z_buffer);
		else
			draw_texture(game, &item->texture, item->pos, z_buffer);
	}
	else if (ft_strcmp(item->name, "chair") == 0)
	{
		if (item->is_broken)
			draw_texture(game, &item->texture_broken, item->pos, z_buffer);
		else
			draw_texture(game, &item->texture, item->pos, z_buffer);
	}
	else
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
