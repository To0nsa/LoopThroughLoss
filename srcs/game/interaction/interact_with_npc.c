/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_npc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:09:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/16 20:46:19 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static t_npc	*find_closest_npc(t_game *game, double max_distance)
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

static bool	advance_npc_dialogue(t_npc *npc, t_story *story)
{
	if (npc->state != SPEAK)
		return (false);
	npc->dialogue.current_line++;
	if (npc->dialogue.current_line
		>= npc->dialogue.count[npc->dialogue.phase])
	{
		npc->dialogue.current_line = 0;
		npc->state = IDLE;
		if (ft_strcmp(npc->type, "mother") == 0)
			story->has_spoken_to_mother = true;
	}
	return (true);
}

bool	continue_npc_dialogue(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 1.1);
	if (!npc || npc->state != SPEAK)
		return (false);
	advance_npc_dialogue(npc, &game->story);
	return (true);
}

static bool	handle_npc_dialogue(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 1.1);
	if (npc->state == NOT_PRESENT)
		return (false);
	if (!npc || npc->state == SPEAK)
		return (false);
	npc->state = SPEAK;
	return (true);
}

bool	interact_with_npc(t_game *game)
{
	return (handle_npc_dialogue(game));
}
