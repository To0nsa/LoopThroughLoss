/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc_dialogue.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:58:30 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/01 15:12:18 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static char	*get_current_dialogue_line(t_npc *npc)
{
	if (npc->dialogue.current_line
		>= npc->dialogue.count[npc->dialogue.phase])
		npc->dialogue.current_line = 0;
	return (npc->dialogue.dialogues
		[npc->dialogue.phase][npc->dialogue.current_line]);
}

void	render_npc_dialogue(t_game *game, t_npc *npc)
{
	if (!npc)
		return;

	(void)game;
	int x = (WIN_W >> 1) - 370;
	int y = WIN_H - (WIN_H / 5);
	int w = 740;
	int h = 80;

	Color box_color = (Color){ 255, 253, 208, 230 };
	Color border_color = GRAY;
	Color text_color = BLACK;

	const char *dialogue_text = get_current_dialogue_line(npc);
	if (!dialogue_text)
		return;

	DrawRectangleRounded((Rectangle){x - 2, y - 2, w + 4, h + 4}, 0.2f, 16, border_color);
	DrawRectangleRounded((Rectangle){x, y, w, h}, 0.2f, 16, box_color);
	DrawTextEx(game->font.dialogue, dialogue_text, (Vector2){x + 20, y + 30}, 24, 1.0f, text_color);
}

static bool	should_draw_npc_dialogue(t_npc *npc)
{
	if (npc->state != SPEAK)
		return (false);
	if (npc->dialogue.phase < 0 || npc->dialogue.phase >= 10)
		return (false);
	if (!npc->dialogue.dialogues[npc->dialogue.phase])
		return (false);
	if (npc->dialogue.current_line < 0
		|| npc->dialogue.current_line
		>= npc->dialogue.count[npc->dialogue.phase])
		npc->dialogue.current_line = 0;
	return (true);
}

void	draw_npc_dialogue(t_game *game)
{
	for (int i = 0; i < game->npc_count; i++)
	{
		if (should_draw_npc_dialogue(game->npcs[i]))
			render_npc_dialogue(game, game->npcs[i]);
	}
}
