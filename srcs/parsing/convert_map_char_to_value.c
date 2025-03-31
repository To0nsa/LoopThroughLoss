/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map_char_to_value.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:39:09 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 18:55:07 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static void	spawn_entity_at_position(t_game *game, char cell,
															double x, double y)
{
	if (cell == 'A')
		spawn_armchair(game, x, y);
	else if (cell == 'B')
		spawn_armchair2(game, x, y);
	else if (cell == 'T')
		spawn_coffee_table(game, x, y);
	else if (cell == 'C')
		spawn_answering_machine(game, x, y);
	else if (cell == 'X')
		spawn_chair(game, x, y);
	else if (cell == 'M')
		spawn_mother(game, x, y);
	else if (cell == 'P')
		spawn_plant(game, x, y);
		
}

static int	get_entity_map_value(char cell)
{
	if (cell == 'A' || cell == 'T' || cell == 'C')
		return (FURNITURE);
	return (EMPTY);
}

static int	spawn_entity(t_game *game, char cell, int x, int y)
{
	spawn_entity_at_position(game, cell, (double)x, (double)y);
	return (get_entity_map_value(cell));
}

int	convert_map_char_to_value(t_game *game, t_map *map, int i, int j)
{
	char	cell;

	cell = map->map_layout[i][j];
	if (cell == '1')
		return (WALL);
	else if (ft_strchr("NSEW", cell))
		return (CONF_DIR);
	else if (cell == '0')
		return (FREE_SPACE);
	else if (cell == 'D')
	{
		spawn_door(game, (double)j, (double)i);
		return (DOOR);
	}
	else if (cell == 'O')
	{
		spawn_frame(game, (double)j, (double)i);
		return (DOOR);
	}
	else
		return (spawn_entity(game, cell, j, i));
}
