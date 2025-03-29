/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_npc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:09:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 14:03:50 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

t_npc	*find_closest_npc(t_game *game, double max_distance)
{
	t_npc	*closest_npc;
	double	closest_dist;
	double	current_dist;
	int		i;

	closest_npc = NULL;
	closest_dist = max_distance;
	i = 0;
	while (i < game->npc_count)
	{
		current_dist
			= ft_euclidean_dist_dpoint(game->player.pos, game->npcs[i]->pos);
		if (current_dist < closest_dist
			&& is_facing_target(&game->player, game->npcs[i]->pos))
		{
			closest_dist = current_dist;
			closest_npc = game->npcs[i];
		}
		i++;
	}
	return (closest_npc);
}

bool	interact_with_npc(t_game *game)
{
	return (handle_npc_dialogue(game));
}
