/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:36:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 07:30:29 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	draw_background(t_game *game)
{
	t_story *story = &game->story;

	DrawRectangle(0, 0, WIN_W, WIN_H / 2, GetColor(CEILING_COLOR_DL));
	DrawRectangle(0, WIN_H / 2, WIN_W, WIN_H / 2, GetColor(FLOOR_COLOR_DL));
}
