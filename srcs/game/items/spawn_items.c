/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:00:12 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 14:24:08 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	spawn_armchair(t_game *game, double x, double y)
{
	t_item		*item;
	t_dpoint	pos;

	item = x_calloc(game, 1, sizeof(t_item));
	pos = (t_dpoint){x, y};
	item->type = "static";
	item->name = "armchair";
	item->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	load_single_xpm(game, &item->texture, FURNITURE_A, game->mlx);
	update_item_list(game, item);
}

void	spawn_console(t_game *game, double x, double y)
{
	t_item		*item;
	t_dpoint	pos;

	item = x_calloc(game, 1, sizeof(t_item));
	pos = (t_dpoint){x, y};
	item->type = "static";
	item->name = "console";
	item->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	load_single_xpm(game, &item->texture, FURNITURE_C, game->mlx);
	update_item_list(game, item);
}

void	spawn_floorlamp(t_game *game, double x, double y)
{
	t_item		*item;
	t_dpoint	pos;

	item = x_calloc(game, 1, sizeof(t_item));
	pos = (t_dpoint){x, y};
	item->type = "static";
	item->name = "floorlamp";
	item->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	load_single_xpm(game, &item->texture, FUNRNITURE_F, game->mlx);
	update_item_list(game, item);
}

void	spawn_coffee_table(t_game *game, double x, double y)
{
	t_item		*item;
	t_dpoint	pos;

	item = x_calloc(game, 1, sizeof(t_item));
	pos = (t_dpoint){x, y};
	item->type = "static";
	item->name = "coffeetable";
	item->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	load_single_xpm(game, &item->texture, FUNRNITURE_CT, game->mlx);
	update_item_list(game, item);
}

void	spawn_chair(t_game *game, double x, double y)
{
	t_item		*item;
	t_dpoint	pos;

	item = x_calloc(game, 1, sizeof(t_item));
	pos = (t_dpoint){x, y};
	item->type = "static";
	item->name = "chair";
	item->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	load_single_xpm(game, &item->texture, ITEM_CHAIR_UP, game->mlx);
	update_item_list(game, item);
}
