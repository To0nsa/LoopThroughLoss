/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_door.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:11:26 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 21:07:06 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

t_door	*find_closest_door(t_game *game, double range)
{
	t_door	*closest_door;
	double	min_distance;
	double	current_distance;
	int		i;

	closest_door = NULL;
	min_distance = range;
	i = 0;
	while (i < game->door_count)
	{
		current_distance
			= ft_euclidean_dist_dpoint(game->player.pos, game->doors[i]->pos);
		if (current_distance <= min_distance)
		{
			min_distance = current_distance;
			closest_door = game->doors[i];
		}
		i++;
	}
	return (closest_door);
}

bool	interact_with_door(t_game *game)
{
	t_door	*door;
	t_story	*story = &game->story;

	door = find_closest_door(game, 1.3);
	if (!door)
		return (false);
	if (door->state == CLOSED && door->type == DOOR_T)
	{
		if (story->state == DENIAL_LOOP)
		{
			show_temp_message(game, 3.0, "Maybe your mother is on the other side of that door ?");
			story->has_interacted_with_door = true;
			story->interaction_timer = 3.0;
		}
		else if (story->state == ANGER_LOOP)
		{
			show_temp_message(game, 3.0, "They will pay for this...");
			story->has_interacted_with_door = true;
			story->interaction_timer = 3.0;
		}
		else if (story->state == BARGAINING_LOOP)
		{
			show_temp_message(game, 3.0, "There must be something more you could have done.");
			story->has_interacted_with_door = true;
			story->interaction_timer = 3.0;
		}
		else if (story->state == DEPRESSION_LOOP)
		{
			show_temp_message(game, 3.0, "What's the point?");
			story->has_interacted_with_door = true;
			story->interaction_timer = 3.0;
		}
		else if (story->state == ACCEPTANCE_LOOP)
		{
			show_temp_message(game, 3.0, "She's dead but not gone.");
			story->has_interacted_with_door = true;
			show_temp_message(game, 3.0, "You carry her, and the mark she made on the world, with you.");
			story->interaction_timer = 3.0;
		}
	}
	if (door->state == CLOSED && door->type == FRAME_T
		&& story->state == BARGAINING_LOOP)
	{
			show_temp_message(game, 3.0, "You try to repair the frame… maybe it’s not too late.");
			story->has_interacted_with_frame = true;
			story->interaction_timer = 3.0;
	}
	return (true);
}
