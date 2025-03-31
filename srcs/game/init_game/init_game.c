/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:19:05 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 08:11:17 by nlouis           ###   ########.fr       */
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
	game->music.voice_message_one = LoadMusicStream(VOICE_MESSAGE1);
	
	return (game);
}
