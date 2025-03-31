/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_item.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:48:46 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 08:17:59 by nlouis           ###   ########.fr       */
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

void update_voice_timer(t_game *game, double delta_time)
{
	if (!game->music.voice_active)
		return;

	UpdateMusicStream(game->music.voice_message_one);
	game->music.voice_timer -= delta_time;

	if (game->music.voice_timer <= 0.0f)
	{
		StopMusicStream(game->music.voice_message_one);
		UnloadMusicStream(game->music.voice_message_one);
		game->music.voice_active = false;
	}
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
			show_temp_message(game, 44.0, "You are listening to the answering machine...");
			PlayMusicStream(game->music.voice_message_one);
			game->music.voice_timer = 44.0;
			game->music.voice_active = true;
			block_interactions_for_seconds(game, 44.0);
			story->reset_timer = 44.0;
		}
		return (true);
	}
	return (true);
}
