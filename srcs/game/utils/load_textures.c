/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:25:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 00:18:38 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	load_single_xpm(t_game *game, t_texture *tex, char *path, void *mlx)
{
	int	width;
	int	height;

	tex->ptr = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!tex->ptr)
		error(game, "mlx_xpm_file_to_image() failed");
	tex->size.x = width;
	tex->size.y = height;
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->line_size,
			&tex->endian);
	if (!tex->addr)
		error(game, "mlx_get_data_addr() failed");
}

void	load_sprite_animation(t_game *game, t_texture **frames,
	char **paths, int frame_count)
{
	int	i;

	*frames = x_calloc(game, frame_count, sizeof(t_texture));
	i = 0;
	while (i < frame_count)
	{
		load_single_xpm(game, &((*frames)[i]), paths[i], game->mlx);
		i++;
	}
}

void	load_game_textures(t_game *game)
{
	load_single_xpm(game, &game->tex.walls, WTEST, game->mlx);
	load_single_xpm(game, &game->tex.door, DTEST, game->mlx);
	load_single_xpm(game, &game->tex.dialogue_box, DIALOGUE_BOX, game->mlx);
}
