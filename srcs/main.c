/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:04:48 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 08:02:03 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		error(NULL, "Usage: ./cub3d <map_file>");

	InitWindow(WIN_W, WIN_H, WIN_NAME);
	InitAudioDevice();
	SetTargetFPS(60);
		
	game = init_game(argv[1]);

	while (!WindowShouldClose())
	{
		game_loop(game);
	}

	// free_game(game);
	CloseWindow();
	return (0);
}
