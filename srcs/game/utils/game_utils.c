/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:08:10 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 22:58:25 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

t_door	*find_door_at(t_game *game, t_point pos)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i]->pos.x == pos.x
			&& game->doors[i]->pos.y == pos.y)
			return (game->doors[i]);
		i++;
	}
	return (NULL);
}
