/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_story_advancement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:08:04 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 10:06:29 by nlouis           ###   ########.fr       */
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
		if (story->loop_number == FIRST_LOOP
			&& !story->has_spoken_to_mother)
			return (PHASE_0);
		else if (story->loop_number == FIRST_LOOP
			&& story->has_spoken_to_mother)
			return (PHASE_1);
		else if (story->loop_number == SECOND_LOOP)
			return (PHASE_4);
	}
	else if (story->state == ANGER_LOOP)
		return (PHASE_2);
	return (PHASE_0);
}

static bool	update_timer(double *timer, double delta_time)
{
	if (*timer <= 0.0)
		return (false);
	*timer -= delta_time;
	if (*timer <= 0.0)
	{
		*timer = 0.0;
		return (true);
	}
	return (false);
}

void	update_story(t_game *game, double delta_time)
{
	t_story	*story = &game->story;
	t_transition *transition = &game->transition;
	t_npc	*mother = NULL;
	t_item	*answering_machine = NULL;

	update_npc_references(game, &mother);
	update_item_references(game, &answering_machine);
	
	if (story->state == DENIAL_LOOP)
	{
		if (story->loop_number == FIRST_LOOP
			&& story->has_spoken_to_mother
			&& update_timer(&story->door_interaction_timer, delta_time))
		{
			story->pending_transition = TRANSITION_FIRST_TO_SECOND_LOOP;
			start_fade_out(transition);
			block_interactions_for_seconds(game, transition->duration);
		}
		else if (story->loop_number == SECOND_LOOP
			&& story->has_spoken_to_mother
			&& update_timer(&story->door_interaction_timer, delta_time))
		{
			story->pending_transition = TRANSITION_SECOND_TO_THIRD_LOOP;
			start_fade_out(transition);
			block_interactions_for_seconds(game, transition->duration);
		}
		else if (story->loop_number == THIRD_LOOP)
		{
			if (story->reset_timer > 0)
			{
				story->reset_timer -= delta_time;
				if (story->reset_timer <= 0)
				{
					story->pending_transition = TRANSITION_THIRD_TO_FOURTH_LOOP;
					start_fade_out(transition);
					block_interactions_for_seconds(game, transition->duration);
				}
			}
		}
	}

	if (transition->state == FADE_IN
		&& story->state == DENIAL_LOOP)
	{
		switch (story->pending_transition)
		{
			case TRANSITION_FIRST_TO_SECOND_LOOP:
				story->loop_number = SECOND_LOOP;
				reset_player(game, &game->player);
				story->has_spoken_to_mother = false;
				story->has_interacted_with_door = false;
				if (mother)
					mother->is_blurry = true;
				break;

			case TRANSITION_SECOND_TO_THIRD_LOOP:
				story->loop_number = THIRD_LOOP;
				reset_player(game, &game->player);
				story->has_spoken_to_mother = false;
				story->has_interacted_with_door = false;
				if (mother)
					mother->state = NOT_PRESENT;
				if (answering_machine)
					answering_machine->is_interactable = true;
				break;

			case TRANSITION_THIRD_TO_FOURTH_LOOP:
				story->state = ANGER_LOOP;
				story->has_spoken_to_mother = false;
				story->has_interacted_with_door = false;
				reset_player(game, &game->player);
				break;

			default:
				break;
		}
		story->pending_transition = TRANSITION_NONE;
	}
	if (mother)
		mother->dialogue.phase = get_mother_dial_phase(&game->story);
}
