/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_dialogue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:17:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 15:15:25 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

bool	advance_npc_dialogue(t_npc *npc, t_story *story)
{
	if (npc->state != SPEAK)
		return (false);
	npc->dialogue.current_line++;
	if (npc->dialogue.current_line
		>= npc->dialogue.dialogue_count[npc->dialogue.phase])
	{
		if (ft_strcmp(npc->type, "mother") == 0)
			story->has_spoken_to_mother = true;
		npc->dialogue.current_line = 0;
		npc->state = IDLE;
	}
	return (true);
}

bool	continue_npc_dialogue(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 2.0);
	if (!npc || npc->state != SPEAK)
		return (false);
	advance_npc_dialogue(npc, game->story);
	return (true);
}

bool	handle_npc_dialogue(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 2.0);
	if (!npc || npc->state == SPEAK)
		return (false);
	npc->state = SPEAK;
	return (true);
}
