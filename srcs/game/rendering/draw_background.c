/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:36:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 15:01:02 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	draw_background(int ceiling_color, int floor_color)
{
	DrawRectangle(0, 0, WIN_W, WIN_H / 2, GetColor(ceiling_color));
	DrawRectangle(0, WIN_H / 2, WIN_W, WIN_H / 2, GetColor(floor_color));
}
