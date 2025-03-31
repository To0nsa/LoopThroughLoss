/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_item.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:48:46 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 17:48:22 by nlouis           ###   ########.fr       */
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

void	update_voice_timer(t_game *game, double delta_time)
{
	if (!game->music.voice_active)
		return;

	if (game->story.state == DENIAL_LOOP)
		UpdateMusicStream(game->music.voice_message_one);
	else if (game->story.state == ANGER_LOOP || game->story.state == BARGAINING_LOOP)
		UpdateMusicStream(game->music.voice_message_two);

	game->music.voice_timer -= delta_time;
	if (game->music.voice_timer <= 0.0)
	{
		if (game->story.state == DENIAL_LOOP)
		{
			StopMusicStream(game->music.voice_message_one);
			game->story.to_anger_loop = true;
		}
		else if (game->story.state == ANGER_LOOP || game->story.state == BARGAINING_LOOP)
			StopMusicStream(game->music.voice_message_two);
		game->music.voice_active = false;
	}
}

static t_item *find_item_by_name(t_game *game, const char *name)
{
	for (int i = 0; i < game->item_count; i++)
	{
		if (ft_strcmp(game->items[i]->name, name) == 0)
			return (game->items[i]);
	}
	return (NULL);
}

bool	interact_with_item(t_game *game)
{
	t_story *story	= &game->story;
	t_item	*item	= find_closest_item(game, 1.1);
	
	if (!item)
		return (false);
	if (item->is_interactable)
	{
		if (story->state == DENIAL_LOOP
			&& story->loop_number == THIRD_LOOP
			&& ft_strcmp(item->name, "answering_machine") == 0)
		{
			show_temp_message(game, 4.0, "You are listening to the answering machine...");
			PlayMusicStream(game->music.voice_message_one);
			SetMusicVolume(game->music.voice_message_one, 0.8f);
			game->music.voice_timer = 4.0;
			game->music.voice_active = true;
			block_interactions_for_seconds(game, 4.0);
			story->reset_timer = 4.0;
		}
		if (story->state == ANGER_LOOP)
		{
			if (story->loop_number == FIRST_LOOP
				&& (ft_strcmp(item->name, "answering_machine") == 0))
			{
				show_temp_message(game, 3.0, "You hit the answering with rage it's broken...");
				story->interaction_timer = 3.0;
				item->is_broken = true;
			}
			if ((story->loop_number == FIRST_LOOP
				|| story->loop_number == SECOND_LOOP)
				&& (ft_strcmp(item->name, "chair") == 0))
			{
				show_temp_message(game, 3.0, "You kicked the chair, it hurts, it makes you angrier...");
				story->interaction_timer = 3.0;
				item->is_broken = true;
			}
			if (story->loop_number == SECOND_LOOP
			&& ft_strcmp(item->name, "answering_machine") == 0)
			{
				t_item *chair = find_item_by_name(game, "chair");
				
				if (chair && chair->is_broken)
				{
					show_temp_message(game, 3.0, "You hit the answering with rage it's broken...");
					story->interaction_timer = 3.0;
					item->is_broken = true;
				}
				else
				{
					show_temp_message(game, 12.0, "You are listening to the answering machine...");
					PlayMusicStream(game->music.voice_message_two);
					SetMusicVolume(game->music.voice_message_two, 0.8f);
					game->music.voice_timer = 12.0;
					story->reset_timer = 12.0;
					game->music.voice_active = true;
					block_interactions_for_seconds(game, 12.0);
				}
			}
		}
		if (story->state == BARGAINING_LOOP)
		{
			if (story->loop_number == FIRST_LOOP)
			{
				if ((ft_strcmp(item->name, "chair") == 0))
				{
					show_temp_message(game, 3.0, "You put back the chair up...");
					story->interaction_timer = 3.0;
					item->is_broken = false;
				}
			}
			if ((story->loop_number == FIRST_LOOP
				||	story->loop_number == SECOND_LOOP)
				&& (ft_strcmp(item->name, "answering_machine") == 0))
			{
				show_temp_message(game, 12.0, "You are listening to the answering machine...");
				PlayMusicStream(game->music.voice_message_two);
				SetMusicVolume(game->music.voice_message_two, 0.8f);
				game->music.voice_timer = 12.0;
				story->reset_timer = 12.0;
				game->music.voice_active = true;
				block_interactions_for_seconds(game, 12.0);
			}
		}
		return (true);
	}
	return (true);
}
