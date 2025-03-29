/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:50:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 13:30:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

bool	is_any_npc_talking(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->npc_count)
	{
		if (game->npcs[i]->state == SPEAK)
			return (true);
		i++;
	}
	return (false);
}

bool	is_wall(t_game *game, t_point pos)
{
	return (game->map->matrix[(int)(pos.y)][(int)pos.x] == WALL);
}
