/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:25:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 20:42:44 by nlouis           ###   ########.fr       */
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
	load_single_texture(game, &game->tex.walls, WTEST);
	load_single_texture(game, &game->tex.door, DTEST);
}
