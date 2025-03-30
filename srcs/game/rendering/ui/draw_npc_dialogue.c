/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc_dialogue.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:58:30 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 15:44:51 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static char	*get_current_dialogue_line(t_npc *npc)
{
	if (npc->dialogue.current_line
		>= npc->dialogue.dialogue_count[npc->dialogue.phase])
		npc->dialogue.current_line = 0;
	return (npc->dialogue.dialogues
		[npc->dialogue.phase][npc->dialogue.current_line]);
}

void	render_npc_dialogue(t_game *game, t_npc *npc)
{
	if (!npc)
		return;

	(void)game;
	int x = (WIN_W >> 1) - 160;
	int y = WIN_H - (WIN_H / 5);
	int w = 320;
	int h = 80;

	Color box_color = Fade(DARKGRAY, 0.6f);     // Fond semi-transparent
	Color border_color = GRAY;
	Color text_color = WHITE;

	const char *dialogue_text = get_current_dialogue_line(npc);
	if (!dialogue_text)
		return;

	// Bordure
	DrawRectangleRounded((Rectangle){x - 2, y - 2, w + 4, h + 4}, 0.2f, 16, border_color);

	// Boîte principale
	DrawRectangleRounded((Rectangle){x, y, w, h}, 0.2f, 16, box_color);

	// Texte
	DrawText(dialogue_text, x + 20, y + 30, 20, text_color);
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
		>= npc->dialogue.dialogue_count[npc->dialogue.phase])
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
