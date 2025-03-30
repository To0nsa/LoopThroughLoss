/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite_screen_coords.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:42:27 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 22:11:47 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static int	get_sprite_screen_x(double transform_x, double transform_y)
{
	return (int)((WIN_W / 2.0) * (1.0 + (transform_x / transform_y)));
}

static int	get_sprite_scaled_size(double transform_y)
{
	int height = (int)fabs((double)WIN_H / transform_y);
	return (height < 1) ? 1 : height;
}

static void	apply_vertical_offset(int *start_y, int *end_y, double vMove, double transform_y)
{
	int vMoveScreen = (int)(vMove / transform_y);
	*start_y += vMoveScreen;
	*end_y += vMoveScreen;
}

static void	get_sprite_bounds(t_sprite_draw *data, int height)
{
	int start_y = -height / 2 + (WIN_H / 2);
	int end_y = start_y + height;

	apply_vertical_offset(&start_y, &end_y, 200.0, data->transform.y);

	data->draw_start.y = start_y;
	data->draw_end.y = end_y;
	data->draw_start.x = data->screen_x - data->width / 2;
	data->draw_end.x = data->screen_x + data->width / 2;
}

static void	clamp_sprite_bounds(t_sprite_draw *data)
{
	if (data->draw_start.x < 0)
		data->draw_start.x = 0;
	if (data->draw_end.x > WIN_W - 1)
		data->draw_end.x = WIN_W - 1;
	if (data->draw_start.y < 0)
		data->draw_start.y = 0;
	if (data->draw_end.y > WIN_H - 1)
		data->draw_end.y = WIN_H - 1;
}

bool	calc_sprite_screen_coords(t_sprite_draw *data)
{
	if (data->transform.y <= 0.0)
		return false;

	data->screen_x = get_sprite_screen_x(data->transform.x, data->transform.y);
	data->height = get_sprite_scaled_size(data->transform.y);
	data->width = data->height;

	get_sprite_bounds(data, data->height);
	clamp_sprite_bounds(data);

	if (data->draw_end.x < 0 || data->draw_start.x >= WIN_W)
		return false;

	return true;
}
