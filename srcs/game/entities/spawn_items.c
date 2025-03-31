/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:00:12 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 20:35:09 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static void	update_item_list(t_game *game, t_item *item)
{
	game->items = x_realloc(game, game->items,
			game->item_count * sizeof(t_item *),
			(game->item_count + 1) * sizeof(t_item *));
	game->items[game->item_count] = item;
	game->item_count++;
}

void	spawn_armchair(t_game *game, double x, double y)
{
	t_item *item = x_calloc(game, 1, sizeof(t_item));
	item->type = "static";
	item->name = "armchair";
	item->pos = (t_dpoint){x + 0.5, y + 0.5};
	load_single_texture(game, &item->texture, FURNITURE_A);
	update_item_list(game, item);
}

void	spawn_armchair2(t_game *game, double x, double y)
{
	t_item *item = x_calloc(game, 1, sizeof(t_item));
	item->type = "static";
	item->name = "armchair2";
	item->pos = (t_dpoint){x + 0.5, y + 0.5};
	load_single_texture(game, &item->texture, FURNITURE_B);
	update_item_list(game, item);
}

void	spawn_answering_machine(t_game *game, double x, double y)
{
	t_item *item = x_calloc(game, 1, sizeof(t_item));
	item->type = "static";
	item->name = "answering_machine";
	item->pos = (t_dpoint){x + 0.5, y + 0.5};
	load_single_texture(game, &item->texture, FURNITURE_C);
	load_single_texture(game, &item->texture_broken, FURNITURE_CB);
	load_single_texture(game, &item->texture_message, FURNITURE_CM);
	update_item_list(game, item);
}

void	spawn_coffee_table(t_game *game, double x, double y)
{
	t_item *item = x_calloc(game, 1, sizeof(t_item));
	item->type = "static";
	item->name = "coffeetable";
	item->pos = (t_dpoint){x + 0.5, y + 0.5};
	load_single_texture(game, &item->texture, FUNRNITURE_CT);
	update_item_list(game, item);
}

void	spawn_chair(t_game *game, double x, double y)
{
	t_item *item = x_calloc(game, 1, sizeof(t_item));
	item->type = "static";
	item->name = "chair";
	item->pos = (t_dpoint){x + 0.5, y + 0.5};
	load_single_texture(game, &item->texture, ITEM_CHAIR_UP);
	load_single_texture(game, &item->texture_broken, ITEM_CHAIR_DOWN);
	update_item_list(game, item);
}

void	spawn_plant(t_game *game, double x, double y)
{
	t_item *item = x_calloc(game, 1, sizeof(t_item));
	item->type = "static";
	item->name = "plant";
	item->pos = (t_dpoint){x + 0.5, y + 0.5};
	load_single_texture(game, &item->texture, PLANT);
	update_item_list(game, item);
}
