/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_story_advancement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:08:04 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/01 16:43:05 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	update_item_references(t_game *game, t_item **answering_machine,
									t_item **chair)
{
	int	i = 0;
	while (i < game->item_count)
	{
		if (ft_strcmp(game->items[i]->name, "answering_machine") == 0)
			*answering_machine = game->items[i];
		if (ft_strcmp(game->items[i]->name, "chair") == 0)
			*chair = game->items[i];
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
		else if (story->loop_number == SECOND_LOOP)
			return (PHASE_1);
	}
	else if (story->state == ANGER_LOOP)
		return (PHASE_2);
	else if (story->state == BARGAINING_LOOP)
		return (PHASE_3);
	else if (story->state == DEPRESSION_LOOP)
		return (PHASE_4);
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
	t_story			*story = &game->story;
	t_transition	*transition = &game->transition;
	t_npc			*mother = NULL;
	t_item			*answering_machine = NULL;
	t_item			*chair = NULL;

	update_npc_references(game, &mother);
	update_item_references(game, &answering_machine, &chair);
	
	if (!game->instruction)
	{
		show_temp_message(game, 3.0, "Press 'E' to interact with elements of the game");
		game->instruction = true;
	}
	if (story->state == DENIAL_LOOP)
	{
		if (story->loop_number == FIRST_LOOP
			&& story->has_spoken_to_mother
			&& story->has_interacted_with_door
			&& update_timer(&story->interaction_timer, delta_time))
		{
			story->pending_transition = TRANSITION_FIRST_TO_SECOND_LOOP;
			start_fade_out(transition);
			block_interactions_for_seconds(game, transition->duration);
		}
		else if (story->loop_number == SECOND_LOOP
			&& story->has_spoken_to_mother
			&& story->has_interacted_with_door
			&& update_timer(&story->interaction_timer, delta_time))
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
					story->pending_transition = TRANSITION_THIRD_TO_ANGER_LOOP;
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
				break ;

			case TRANSITION_SECOND_TO_THIRD_LOOP:
				story->loop_number = THIRD_LOOP;
				reset_player(game, &game->player);
				story->has_spoken_to_mother = false;
				story->has_interacted_with_door = false;
				if (mother)
					mother->state = NOT_PRESENT;
				if (answering_machine)
				{
					answering_machine->is_interactable = true;
					answering_machine->has_message = true;
				}
				break ;

			case TRANSITION_THIRD_TO_ANGER_LOOP:
			
				story->state = ANGER_LOOP;
				story->loop_number = FIRST_LOOP;
				story->has_spoken_to_mother = false;
				story->has_interacted_with_door = false;
				story->has_repaired_frame = false;
				if (mother)
					mother->state = IDLE;	
				if (answering_machine)
				{
					answering_machine->is_interactable = true;
					answering_machine->has_message = false;
				}
				if (chair)
				{
					chair->is_interactable = true;
					chair->is_broken = false;
				}
				reset_player(game, &game->player);
				break;

			default:
				break ;
		}
		story->pending_transition = TRANSITION_NONE;
	}

	if (story->state == ANGER_LOOP)
	{	
		if (story->loop_number == FIRST_LOOP
			&& story->has_spoken_to_mother
			&& story->has_interacted_with_door
			&& chair->is_broken && answering_machine->is_broken
			&& update_timer(&story->interaction_timer, delta_time))
		{
			story->pending_transition = TRANSITION_FIRST_TO_SECOND_LOOP;
			start_fade_out(transition);
			block_interactions_for_seconds(game, transition->duration);
		}
		else if (story->loop_number == SECOND_LOOP)
		{
			if (chair->is_broken
				&& story->has_interacted_with_door
				&& update_timer(&story->interaction_timer, delta_time))
			{
				story->pending_transition = TRANSITION_RESET_SECOND_LOOP;
				start_fade_out(transition);
				block_interactions_for_seconds(game, transition->duration);
			}
			if (!chair->is_broken && update_timer(&story->reset_timer, delta_time))
			{
				story->pending_transition = TRANSITION_SECOND_TO_BARGAINING_LOOP;
				start_fade_out(transition);
				block_interactions_for_seconds(game, transition->duration);
			}
		}
	}

	if (transition->state == FADE_IN
		&& story->state == ANGER_LOOP)
	{
		switch (story->pending_transition)
		{
			case TRANSITION_FIRST_TO_SECOND_LOOP:
				story->loop_number = SECOND_LOOP;
				reset_player(game, &game->player);
				story->has_spoken_to_mother = false;
				story->has_interacted_with_door = false;
				if (chair)
					chair->is_broken = false;
				if (answering_machine)
				{
					answering_machine->is_broken = false;
					answering_machine->has_message = true;
				}
				if (mother)
					mother->state = NOT_PRESENT;
				break ;

			case TRANSITION_RESET_SECOND_LOOP:
				story->loop_number = SECOND_LOOP;
				reset_player(game, &game->player);
				story->has_spoken_to_mother = false;
				story->has_interacted_with_door = false;
				if (chair)
					chair->is_broken = false;
				if (answering_machine)
				{
					answering_machine->is_broken = false;
					answering_machine->has_message = true;
				}
				if (mother)
					mother->state = NOT_PRESENT;
				break ;

			case TRANSITION_SECOND_TO_BARGAINING_LOOP:
				story->loop_number = FIRST_LOOP;
				story->state = BARGAINING_LOOP;
				reset_player(game, &game->player);
				story->has_spoken_to_mother = false;
				story->has_interacted_with_door = false;
				if (mother)
					mother->state = NOT_PRESENT;
				if (answering_machine)
				{
					answering_machine->is_interactable = true;
					answering_machine->has_message = true;
				}
				if (chair)
					chair->is_broken = true;
				break ;

			default:
				break ;
		}
		story->pending_transition = TRANSITION_NONE;
	}

	if (story->state == BARGAINING_LOOP)
	{	
		if (story->loop_number == FIRST_LOOP
			&& story->has_repaired_frame
			&& story->has_interacted_with_door
			&& !chair->is_broken
			&& update_timer(&story->interaction_timer, delta_time))
		{
			story->pending_transition = TRANSITION_FIRST_TO_SECOND_LOOP;
			start_fade_out(transition);
			block_interactions_for_seconds(game, transition->duration);
		}
		else if (story->loop_number == SECOND_LOOP)
		{
			if (story->has_interacted_with_door
				&& story->has_spoken_to_mother
				&& story->has_repaired_frame
				&& update_timer(&story->interaction_timer, delta_time))
			{
				story->pending_transition = TRANSITION_SECOND_LOOP_TO_DEPRESSION;
				start_fade_out(transition);
				block_interactions_for_seconds(game, transition->duration);
			}
		}
	}

	if (transition->state == FADE_IN
		&& story->state == BARGAINING_LOOP)
	{
		switch (story->pending_transition)
		{
			case TRANSITION_FIRST_TO_SECOND_LOOP:
				story->loop_number = SECOND_LOOP;
				reset_player(game, &game->player);
				story->has_spoken_to_mother = false;
				story->has_interacted_with_door = false;
				story->has_repaired_frame = false;
				if (chair)
				{
					chair->is_interactable = true;
					chair->is_broken = false;
				}
				if (answering_machine)
				{
					answering_machine->is_broken = false;
					answering_machine->has_message = true;
				}
				if (mother)
					mother->state = IDLE;
				break ;

			case TRANSITION_SECOND_LOOP_TO_DEPRESSION:
				story->loop_number = FIRST_LOOP;
				story->state = DEPRESSION_LOOP;
				reset_player(game, &game->player);
				story->has_interacted_with_door = false;
				story->has_spoken_to_mother = false;
				if (answering_machine)
				{
					answering_machine->is_broken = false;
					answering_machine->has_message = false;
				}
				if (mother)
				{
					mother->state = IDLE;
					mother->is_blurry = true;
				}
				if (chair)
				{
					chair->is_interactable = false;
					chair->is_broken = false;
				}
				story->reset_timer = 16.0;
				break ;

			default:
				break ;
		}
		story->pending_transition = TRANSITION_NONE;
	}

	if (story->state == DEPRESSION_LOOP)
	{	
		if (game->player.pos.y == story->last_player_pos.y
			&& game->player.pos.x == story->last_player_pos.x)
		{
			if (!story->is_player_idle)
			{
				story->is_player_idle = true;
				story->reset_timer = 8.0;
			}
		}
		else
		{
			story->is_player_idle = false;
			story->reset_timer = 8.0;
		}
		story->last_player_pos = game->player.pos;
		
		if (story->loop_number == FIRST_LOOP
			&& story->has_interacted_with_door
			&& update_timer(&story->interaction_timer, delta_time))
		{
			story->pending_transition = TRANSITION_RESET_FIRST_LOOP;
			start_fade_out(transition);
			block_interactions_for_seconds(game, transition->duration);
		}
		else if (story->loop_number == FIRST_LOOP
			&& story->is_player_idle
			&& story->has_spoken_to_mother
			&& update_timer(&story->reset_timer, delta_time))
		{
			story->pending_transition = TRANSITION_FIRST_TO_ACCEPTANCE_LOOP;
			start_fade_out(transition);
			block_interactions_for_seconds(game, transition->duration);
		}
	}

	if (transition->state == FADE_IN
		&& story->state == DEPRESSION_LOOP)
	{
		switch (story->pending_transition)
		{
			case TRANSITION_RESET_FIRST_LOOP:
				reset_player(game, &game->player);
				story->has_interacted_with_door = false;
				break ;

			case TRANSITION_FIRST_TO_ACCEPTANCE_LOOP:
				story->loop_number = FIRST_LOOP;
				story->state = ACCEPTANCE_LOOP;
				reset_player(game, &game->player);
				story->has_interacted_with_door = false;
				if (mother)
				{
					mother->state = NOT_PRESENT;
				}
				break ;

			default:
				break ;
		}
		story->pending_transition = TRANSITION_NONE;
	}

	if (game->story.state == ACCEPTANCE_LOOP && game->story.has_interacted_with_door)
	{
		game->story.cover_progress += delta_time * 0.50f;

		if (game->story.cover_progress > 1.0f)
			game->story.cover_progress = 1.0f;
	}

	if (mother)
		mother->dialogue.phase = get_mother_dial_phase(&game->story);
}
