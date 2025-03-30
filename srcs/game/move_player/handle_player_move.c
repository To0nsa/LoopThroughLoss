/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player_move.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:28:44 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 20:05:26 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static bool	is_any_npc_talking(t_game *game)
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

static bool	is_answering_machine_on(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->item_count)
	{
		if (ft_strcmp(game->items[i]->name, "answering_machine") == 0
			&& game->items[i]->state == ON)
			return (true);
		i++;
	}
	return (false);
}

void	handle_player_moves(t_game *game, double delta_time)
{
	t_player	*player = &game->player;

	if (is_any_npc_talking(game)
		|| is_answering_machine_on(game)
		|| game->transition.on)
		return ;

	if (game->keys[KEY_W])
		move_player_forward(game, player, delta_time);
	if (game->keys[KEY_S])
		move_player_backward(game, player, delta_time);
	if (game->keys[KEY_A])
		strafe_player_left(game, player, delta_time);
	if (game->keys[KEY_D])
		strafe_player_right(game, player, delta_time);
	if (game->keys[KEY_RIGHT])
		rotate_player_right(player, delta_time);
	if (game->keys[KEY_LEFT])
		rotate_player_left(player, delta_time);
}
