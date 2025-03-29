/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:13:03 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 14:08:11 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static bool	interact_with_sorted_entities(t_game *game)
{
	t_entity	*entity;
	double		interaction_range;
	double		dist;
	int			i;

	interaction_range = 2.0;
	i = -1;
	while (++i < game->entity_count)
	{
		entity = &game->entities[i];
		dist = ft_euclidean_dist_dpoint(game->player.pos, entity->pos);
		if (dist > interaction_range)
			continue ;
		if (!is_facing_target(&game->player, entity->pos))
			continue ;
		if (entity->type == ITEM && interact_with_item(game))
			return (true);
		if (entity->type == NPC && interact_with_npc(game))
			return (true);
	}
	return (false);
}

void	handle_interaction(t_game *game)
{
	if (continue_npc_dialogue(game))
		return ;
	if (interact_with_sorted_entities(game))
		return ;
	interact_with_door(game);
}
