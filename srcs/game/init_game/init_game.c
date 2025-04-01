/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:19:05 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/01 16:42:43 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static t_map	*init_map(t_game *game, char *filename)
{
	t_map	*map;

	map = x_calloc(game, 1, sizeof(t_map));
	map->filename = filename;
	map->floor_color = FLOOR_COLOR_DL;
	map->ceiling_color = CEILING_COLOR_DL;
	return (map);
}

t_game	*init_game(char *filename)
{
	t_game	*game;

	game = x_calloc(NULL, 1, sizeof(t_game));
	game->map = init_map(game, filename);
	parse_map(game, game->map);
	load_game_textures(game);
	init_player(game, &game->player);
	init_transition(game, &game->transition, 4.0);
	game->state = RUNNING;
	game->story.state = DENIAL_LOOP;
	game->story.loop_number = FIRST_LOOP;
	game->font.dialogue = LoadFont(M_FONT);
	game->font.interaction = LoadFont(I_FONT);
	
	game->music.voice_message_one.music = LoadMusicStream(VOICE_MESSAGE1);
	game->music.voice_message_one.volume = 0.0f;
	game->music.voice_message_one.is_playing = false;
	
	game->music.voice_message_two.music = LoadMusicStream(VOICE_MESSAGE2);
	game->music.voice_message_two.volume = 0.0f;
	game->music.voice_message_two.is_playing = false;
	
	game->music.denial.music = LoadMusicStream(MUSIC_DENIAL);
	game->music.denial.volume = 0.0f;
	game->music.denial.is_playing = false;
	
	game->music.acceptance.music = LoadMusicStream(MUSIC_ACCEPTANCE);
	game->music.acceptance.volume = 0.0f;
	game->music.acceptance.is_playing = false;
	
	game->music.bargaining.music = LoadMusicStream(MUSIC_BARGAINING);
	game->music.bargaining.volume = 0.0f;
	game->music.bargaining.is_playing = false;
	
	game->music.anger.music = LoadMusicStream(MUSIC_ANGRY);
	game->music.anger.volume = 0.0f;
	game->music.anger.is_playing = false;
	
	game->music.depression.music = LoadMusicStream(MUSIC_DEPRESSION);
	game->music.depression.volume = 0.0f;
	game->music.depression.is_playing = false;

	game->instruction = false;
	return (game);
}
