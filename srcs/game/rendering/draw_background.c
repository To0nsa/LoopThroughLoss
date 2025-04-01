/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:36:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/01 14:04:18 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	draw_background(t_game *game)
{
	t_story *story = &game->story;

	if (story->state == DENIAL_LOOP)
	{
		DrawRectangle(0, 0, WIN_W, WIN_H / 2, GetColor(CEILING_COLOR_DL));
		DrawRectangle(0, WIN_H / 2, WIN_W, WIN_H / 2, GetColor(FLOOR_COLOR_DL));
	}
	else if (story->state == ANGER_LOOP)
	{
		DrawRectangle(0, 0, WIN_W, WIN_H / 2, GetColor(CEILING_COLOR_AL));
		DrawRectangle(0, WIN_H / 2, WIN_W, WIN_H / 2, GetColor(FLOOR_COLOR_AL));
	}
	else if (story->state == BARGAINING_LOOP)
	{
		DrawRectangle(0, 0, WIN_W, WIN_H / 2, GetColor(CEILING_COLOR_BL));
		DrawRectangle(0, WIN_H / 2, WIN_W, WIN_H / 2, GetColor(FLOOR_COLOR_BL));
	}
	else if (story->state == DEPRESSION_LOOP)
	{
		DrawRectangle(0, 0, WIN_W, WIN_H / 2, GetColor(CEILING_COLOR_DEPL));
		DrawRectangle(0, WIN_H / 2, WIN_W, WIN_H / 2, GetColor(FLOOR_COLOR_DEPL));
	}
	else if (story->state == ACCEPTANCE_LOOP)
	{
		DrawRectangle(0, 0, WIN_W, WIN_H / 2, GetColor(CEILING_COLOR_ACCL));
		DrawRectangle(0, WIN_H / 2, WIN_W, WIN_H / 2, GetColor(FLOOR_COLOR_ACCL));
	}
}
