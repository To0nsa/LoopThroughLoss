/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_item.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:48:46 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 23:23:28 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static t_item	*find_closest_item(t_game *game, double range)
{
	t_item	*closest_item;
	double	min_distance;
	double	current_distance;
	int		i;

	closest_item = NULL;
	min_distance = range;
	i = 0;
	while (i < game->item_count)
	{
		current_distance
			= ft_euclidean_dist_dpoint(game->player.pos, game->items[i]->pos);
		if (current_distance <= min_distance
			&& is_facing_target(&game->player, game->items[i]->pos))
		{
			min_distance = current_distance;
			closest_item = game->items[i];
		}
		i++;
	}
	return (closest_item);
}

bool	interact_with_item(t_game *game)
{
	t_story *story	= &game->story;
	t_item	*item	= find_closest_item(game, 1.5);
	if (!item)
		return (false);
	if (item->is_interactable)
	{
		if (story->state == DENIAL_LOOP
			&& story->loop_number == THIRD_LOOP
			&& ft_strcmp(item->name, "answering_machine") == 0)
		{
			item->state = ON;
			show_temp_message(game, 8.0, "You are listening to the answering machine.");
			// play denial loop voice message
			block_interactions_for_seconds(game, 8.0);
			story->reset_timer = 8.0;
		}
		return (true);
	}
	return (true);
}
