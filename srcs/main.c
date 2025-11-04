/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:04:48 by nlouis            #+#    #+#             */
/*   Updated: 2025/11/04 12:23:32 by nlouis           ###   ########.fr       */
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
	SetTargetFPS(60);
		
	game = init_game(map_path);

	while (!WindowShouldClose())
	{
		game_loop(game);
	}

	CloseWindow();
	free_game(game);
	return (0);
}
