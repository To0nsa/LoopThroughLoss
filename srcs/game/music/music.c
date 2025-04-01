/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:18:42 by riamaev           #+#    #+#             */
/*   Updated: 2025/04/01 22:30:57 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void fade_music_volume(t_track *track, float target_volume, float fade_speed, double delta_time)
{
	if (track->volume < target_volume)
	{
		track->volume += fade_speed * delta_time;
		if (track->volume > target_volume)
			track->volume = target_volume;
	}
	else if (track->volume > target_volume)
	{
		track->volume -= fade_speed * delta_time;
		if (track->volume < target_volume)
			track->volume = target_volume;
	}
	SetMusicVolume(track->music, track->volume);
}

void update_music(t_game *game, double delta_time)
{
	t_track	*current_music = NULL;

	if (game->music.voice_active || game->transition.state != FADE_IDLE)
		current_music = NULL;
	else
	{
		if (game->story.state == DENIAL_LOOP)
			current_music = &game->music.denial;
		else if (game->story.state == ANGER_LOOP)
			current_music = &game->music.anger;
		else if (game->story.state == BARGAINING_LOOP)
			current_music = &game->music.bargaining;
		else if (game->story.state == DEPRESSION_LOOP)
			current_music = &game->music.depression;
		else if (game->story.state == ACCEPTANCE_LOOP)
			current_music = &game->music.acceptance;
	}

	float fade_speed = 0.5f;

	t_track *tracks[] = {
		&game->music.denial, &game->music.anger, &game->music.bargaining,
		&game->music.depression, &game->music.acceptance
	};

	for (int i = 0; i < 5; i++)
	{
		t_track *track = tracks[i];
		if (track == current_music)
		{
			if (!track->is_playing)
			{
				PlayMusicStream(track->music);
				track->is_playing = true;
			}
			fade_music_volume(track, 0.4f, fade_speed, delta_time);
		}
		else
		{
			fade_music_volume(track, 0.0f, fade_speed, delta_time);
			if (track->is_playing && track->volume <= 0.01f)
			{
				StopMusicStream(track->music);
				track->is_playing = false;
			}
		}
		if (track->is_playing)
			UpdateMusicStream(track->music);
	}

	if (game->music.voice_active)
	{
		if (game->story.state == DENIAL_LOOP)
			UpdateMusicStream(game->music.voice_message_one.music);
		else if (game->story.state == ANGER_LOOP || game->story.state == BARGAINING_LOOP)
			UpdateMusicStream(game->music.voice_message_two.music);
	}
}

