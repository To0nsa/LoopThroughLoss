/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_story_advancement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:08:04 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 23:46:55 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static void	update_item_references(t_game *game, t_item **answering_machine)
{
	int	i = 0;
	while (i < game->item_count)
	{
		if (ft_strcmp(game->items[i]->name, "answering_machine") == 0)
			*answering_machine = game->items[i];
		i++;
	}
}

static void	update_npc_references(t_game *game, t_npc **mother)
{
	int	i = 0;

	while (i < game->npc_count)
	{
		if (ft_strcmp(game->npcs[i]->type, "mother") == 0)
			*mother = game->npcs[i];
		i++;
	}
}

static t_dial_phase	get_mother_dial_phase(t_story *story)
{
	if (story->state == DENIAL_LOOP)
	{
		if (story->loop_number == FIRST_LOOP)
			return (PHASE_0);
		else
			return (PHASE_1);
	}
	else if (story->state == ANGER_LOOP)
		return (PHASE_2);
	return (PHASE_0);
}

void	update_story(t_game *game, double delta_time)
{
	t_story	*story = &game->story;
	t_npc	*mother = NULL;
	t_item	*answering_machine = NULL;

	update_npc_references(game, &mother);
	update_item_references(game, &answering_machine);
	if (story->state == DENIAL_LOOP)
	{
		if (story->loop_number == FIRST_LOOP
			&& story->has_spoken_to_mother
			&& story->has_interacted_with_door)
		{
			story->loop_number = SECOND_LOOP;
			mother->state = BLURRY;
			start_fade_out(&game->transition);
			block_interactions_for_seconds(game, game->transition.duration);
		}
		else if (story->loop_number == SECOND_LOOP
			&& story->has_spoken_to_mother
			&& story->has_interacted_with_door)
		{
			story->loop_number = THIRD_LOOP;
			mother->state = NOT_PRESENT;
			answering_machine->is_interactable = true;
			start_fade_out(&game->transition);
			block_interactions_for_seconds(game, game->transition.duration);
		} 
		else if (story->loop_number == THIRD_LOOP)
		{
			if (story->reset_timer > 0)
			{
				story->reset_timer -= delta_time;
				if (story->reset_timer <= 0)
				{
					start_fade_out(&game->transition);
					block_interactions_for_seconds(game, game->transition.duration);
				}
			}
		}
	}
	mother->dialogue.phase = get_mother_dial_phase(&game->story);
}
