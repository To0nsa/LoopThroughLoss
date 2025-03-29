/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:06:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 15:30:24 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static void	parse_map_layout(t_game *game, t_map *map)
{
	int	row;
	int	col;

	calculate_map_dimension(game, map);
	normalize_map_layout(game, map);
	row = 0;
	while (row < map->size.y)
	{
		col = 0;
		while (col < (int)ft_strlen(map->map_layout[row]))
		{
			process_map_cell(game, map, row, col);
			col++;
		}
		row++;
	}
	if (map->player_count != 1)
		error(game, "Map must have exactly one player starting position");
}

static void	parse_content(t_game *game, t_map *map)
{
	map->map_layout = x_copy_strarray(game, map->file_content);
	parse_map_layout(game, map);
}

static void	map_layout_to_matrix(t_game *game, t_map *map)
{
	int	i;
	int	j;

	map->matrix = x_create_matrix(game, map->size.y, map->size.x);
	i = 0;
	while (i < map->size.y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map_layout[i]))
		{
			map->matrix[i][j] = convert_map_char_to_value(game, map, i, j);
			j++;
		}
		i++;
	}
}

void	parse_map(t_game *game, t_map *map)
{
	extract_file_content(game, map);
	parse_content(game, map);
	map_layout_to_matrix(game, map);
}
