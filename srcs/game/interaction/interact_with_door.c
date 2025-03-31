/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_door.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:11:26 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 11:25:17 by ahavu            ###   ########.fr       */
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

	door = find_closest_door(game, 2.0);
	if (!door)
		return (false);
	if (door->state == CLOSED)
	{
		if (story->state == DENIAL_LOOP)
		{
			show_temp_message(game, 3.0, "Maybe your mother is on the other side of that door?");
			story->door_interaction_timer = 3.0;
		}
		else if (story->state == ANGER_LOOP)
		{
			show_temp_message(game, 3.0, "They will pay for this...");
			story->door_interaction_timer = 3.0;
		}
		else if (story->state == BARGAINING_LOOP)
		{
			show_temp_message(game, 3.0, "There must be something more you could have done.");
			story->door_interaction_timer = 3.0;
		}
		else if (story->state == DEPRESSION_LOOP)
		{
			show_temp_message(game, 3.0, "What's the point?");
			story->door_interaction_timer = 3.0;
		}
		else if (story->state == ACCEPTANCE_LOOP)
		{
			show_temp_message(game, 3.0, "She's dead but not gone.");
			show_temp_message(game, 3.0, "You carry her, and the mark she made on the world, with you.");
			story->door_interaction_timer = 3.0;
		}
	}
	return (true);
}
