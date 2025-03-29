/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 00:39:41 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

void	render_scene(t_game *game, double delta_time)
{
	t_ray	ray;
	double	*z_buffer;

	(void)delta_time;
	
	z_buffer = x_calloc(game, WIN_W, sizeof(double));
	
	game->img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
									&game->img.bpp,
									&game->img.line_size,
									&game->img.endian);
	ft_memcpy(game->img.addr, game->bg_img.addr, WIN_W * WIN_H * (game->img.bpp / 8));
	
	int	x = 0;
	while (x < WIN_W)
		raycast(game, &ray, &x, z_buffer);
	draw_entities(game, z_buffer);
	mlx_put_image_to_window(game->mlx, game->window->ptr, game->img.ptr, 0, 0);
	
	draw_npc_dialogue(game);
	draw_temp_message(game);

	render_transition(game, &game->transition);
	
	mlx_destroy_image(game->mlx, game->img.ptr);
	free(z_buffer);
}
