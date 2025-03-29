/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_door.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:11:26 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 15:16:26 by nlouis           ###   ########.fr       */
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
		if (current_distance <= min_distance
			&& is_facing_target(&game->player, game->doors[i]->pos))
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

	door = find_closest_door(game, 2.0);
	if (!door)
		return (false);
	if (door->state == CLOSED)
	{
		if (game->story->state == ACCEPTANCE_LOOP)
		{
			show_temp_message(game, 3.0, "Why leave, you are good here...");
		}
		else if (game->story->state == ANGER_LOOP)
		{
			show_temp_message(game, 3.0, "How are you feeling today?");
		}
		else if (game->story->state == BARGAINING_LOOP)
		{
			show_temp_message(game, 3.0, "Are you feeling better now?");
		}
		else if (game->story->state == DEPRESSION_LOOP)
		{
			show_temp_message(game, 3.0, "What's the point?");
		}
		else if (game->story->state == ACCEPTANCE_LOOP)
		{
			// endgame(game);
		}
	}
	return (true);
}
