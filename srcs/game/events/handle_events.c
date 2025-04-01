/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:17:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/01 23:49:54 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	handle_events(t_game *game)
{
	if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
	{
		free_game(game);
		exit(EXIT_SUCCESS);
	}

	if (IsKeyPressed(KEY_E))
		handle_interaction(game);

	game->keys[KEY_W] = IsKeyDown(KEY_W);
	game->keys[KEY_A] = IsKeyDown(KEY_A);
	game->keys[KEY_S] = IsKeyDown(KEY_S);
	game->keys[KEY_D] = IsKeyDown(KEY_D);

	game->keys[KEY_LEFT] = IsKeyDown(KEY_LEFT);
	game->keys[KEY_RIGHT] = IsKeyDown(KEY_RIGHT);
}
