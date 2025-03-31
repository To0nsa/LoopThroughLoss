/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:25:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 20:43:30 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	load_single_texture(t_game *game, t_texture *tex, const char *path)
{
	tex->texture = LoadTexture(path);
	if (tex->texture.id == 0)
		error(game, "LoadTexture() failed");

	tex->size.x = tex->texture.width;
	tex->size.y = tex->texture.height;
}

void	load_sprite_animation(t_game *game, t_texture **frames,
	char **paths, int frame_count)
{
	int	i;

	*frames = x_calloc(game, frame_count, sizeof(t_texture));
	for (i = 0; i < frame_count; i++)
		load_single_texture(game, &((*frames)[i]), paths[i]);
}

void	load_game_textures(t_game *game)
{
	load_single_texture(game, &game->tex.walls_denial, WALL_DENIAL);
	load_single_texture(game, &game->tex.door_denial, DOOR_DENIAL);
	load_single_texture(game, &game->tex.frame_denial, DOOR_FRAME_DENIAL);

	load_single_texture(game, &game->tex.walls_angry, WALL_ANGRY);
	load_single_texture(game, &game->tex.door_angry, DOOR_ANGRY);
	load_single_texture(game, &game->tex.frame_angry, DOOR_FRAME_ANGRY);

	load_single_texture(game, &game->tex.walls_acceptance, WALL_ACCEPTANCE);
	load_single_texture(game, &game->tex.door_acceptance, DOOR_ACCEPTANCE);
	load_single_texture(game, &game->tex.frame_acceptance, DOOR_FRAME_ACCEPTANCE);

	load_single_texture(game, &game->tex.walls_bargaining, WALL_BARGAINING);
	load_single_texture(game, &game->tex.door_bargaining, DOOR_BARGAINING);
	load_single_texture(game, &game->tex.frame_bargaining, DOOR_FRAME_BARGAINING);
	load_single_texture(game, &game->tex.frame_bargaining_repaired, DOOR_FRAME_BARGAINING_REPAIRED);

	load_single_texture(game, &game->tex.walls_sad, WALL_SAD);
	load_single_texture(game, &game->tex.door_sad, DOOR_SAD);
	load_single_texture(game, &game->tex.frame_sad, DOOR_FRAME_SAD);
}
