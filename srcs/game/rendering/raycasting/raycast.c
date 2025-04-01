/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:05:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/01 12:21:24 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static inline t_texture	*select_wall_texture(t_game *game, t_ray *ray)
{
	t_story *story = &game->story;
	t_door	*door;

	if (ray->hit == 2)
	{
		door = find_door_at(game, ray->map);
		if (door)
		{
			if (strcmp(door->name, "door") == 0)
			{
				if (story->state == DENIAL_LOOP)
					return &game->tex.door_denial;
				else if (story->state == ANGER_LOOP)
					return &game->tex.door_angry;
				else if (story->state == BARGAINING_LOOP)
					return &game->tex.door_bargaining;
				else if (story->state == DEPRESSION_LOOP)
					return &game->tex.door_sad;
				else if (story->state == ACCEPTANCE_LOOP)
					return &game->tex.door_acceptance;
			}
			else if (strcmp(door->name, "frame") == 0)
			{
				if (story->state == DENIAL_LOOP)
					return &game->tex.frame_denial;
				else if (story->state == ANGER_LOOP)
					return &game->tex.frame_angry;
				else if (story->state == DEPRESSION_LOOP)
					return &game->tex.frame_sad;
				else if (story->state == ACCEPTANCE_LOOP)
					return &game->tex.frame_acceptance;
				else if (story->state == BARGAINING_LOOP)
				{
					if (story->has_repaired_frame)
						return &game->tex.frame_bargaining_repaired;
					else
						return &game->tex.frame_bargaining;
				}
			}
		}
	}

	if (ray->side == 0 || ray->side == 1)
	{
		if (story->state == DENIAL_LOOP)
			return &game->tex.walls_denial;
		else if (story->state == ANGER_LOOP)
			return &game->tex.walls_angry;
		else if (story->state == BARGAINING_LOOP)
			return &game->tex.walls_bargaining;
		else if (story->state == DEPRESSION_LOOP)
			return &game->tex.walls_sad;
		else if (story->state == ACCEPTANCE_LOOP)
			return &game->tex.walls_acceptance;
	}

	return &game->tex.walls_denial;
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
