/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:04:48 by nlouis            #+#    #+#             */
/*   Updated: 2025/11/05 11:26:35 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

int	main()
{
	t_game		*game;
	char	*map_path;

	map_path = "maps/LoopThroughLoss.cub";

	InitWindow(WIN_W, WIN_H, WIN_NAME);
	InitAudioDevice();
#ifdef PLATFORM_WEB
	// Let the browser rAF drive frame pacing to avoid jitter/flicker
	SetTargetFPS(0);
#else
	SetTargetFPS(60);
#endif
		
	game = init_game(map_path);

	while (!WindowShouldClose())
	{
		game_loop(game);
	}

	CloseWindow();
	free_game(game);
	return (0);
}
