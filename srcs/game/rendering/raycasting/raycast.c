/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:05:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 17:14:04 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static inline t_texture	*select_wall_texture(t_game *game, t_ray *ray)
{
	t_door	*door;

	if (ray->hit == 2)
	{
		door = find_door_at(game, ray->map);
		if (door && door->type == DOOR_T)
			return (&game->tex.door);
		if (door && door->type == FRAME_T)
			return (&game->tex.frame);
		if (door && door->type == FRAME_T && door->is_broken)
			return (&game->tex.frame_broken);	
	}
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (&game->tex.walls);
		else
			return (&game->tex.walls);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&game->tex.walls);
		else
			return (&game->tex.walls);
	}
	(void)ray;
	return (&game->tex.walls);
}

void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	t_texture	*tex = select_wall_texture(game, ray);

	Rectangle src_rect = {
		.x = ray->tex.x,
		.y = 0,
		.width = 1,
		.height = tex->size.y
	};

	Rectangle dest_rect = {
		.x = x,
		.y = ray->draw_start,
		.width = 1,
		.height = ray->draw_end - ray->draw_start
	};

	Vector2 origin = {0, 0};

	DrawTexturePro(tex->texture, src_rect, dest_rect, origin, 0, WHITE);
}

void	raycast(t_game *game, t_ray *ray, int x, double *z_buffer)
{
	init_ray(game, ray, x);
	init_dda_ray(game, ray);
	perform_dda(game, ray);
	calculate_ray_properties(game, ray);
	draw_wall_column(game, ray, x);
	z_buffer[x] = ray->perp_w_dist;
}
