/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_mother.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:23:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/01 14:21:55 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static void	update_npc_list(t_game *game, t_npc *npc)
{
	game->npcs = x_realloc(game, game->npcs,
			game->npc_count * sizeof(t_npc *),
			(game->npc_count + 1) * sizeof(t_npc *));
	game->npcs[game->npc_count] = npc;
	game->npc_count++;
}

static void	allocate_dialogues(t_game *game, t_dial *dialog, char *dialogues[][6], int phase_count)
{
	int	i = 0;
	int	count;
	int	j;

	dialog->dialogues = x_malloc(game, phase_count * sizeof(char **));
	dialog->count = x_malloc(game, phase_count * sizeof(int));
	while (i < phase_count)
	{
		count = 0;
		while (dialogues[i][count])
			count++;
		dialog->dialogues[i] = x_malloc(game, (count + 1) * sizeof(char *));
		if (!dialog->dialogues[i])
			return ;
		dialog->count[i] = count;
		j = 0;
		while (j < count)
		{
			dialog->dialogues[i][j] = x_strdup(game, dialogues[i][j]);
			j++;
		}
		dialog->dialogues[i][count] = NULL;
		i++;
	}
}


void	init_mother_dialogues(t_game *game, t_npc *npc)
{
	static char	*mother_dialogues[][6] = {
		{"Sweetheart, I'm still here... It's just a little scare.",							// denial loop, first iteration PHASE_0
			"The doctors said I'll be fine. We have all the time in the world.", 
			"We're not done making memories together, remember?", NULL },
		{"I'll walk through that door any minute now. Keep your eyes on it...",
			"I'm not going anywhere. I'm always right here with you.", NULL },				// denial loop, other iterations PHASE_1
		{"You should've pushed harder for me. Why didn't you fight for better care?",
			"They let me slip away, and you just stood there... How could you?", NULL }, 	// anger loop PHASE_2
		{"If only we'd found that one specialist... I'd still be by your side.",
			"There must have been another treatment out there, something we missed.", NULL }, 										// bargaining loop PHASE_3
		{"I hate seeing how lost you are without me... but I can't reach you anymore.",
			"What will you do when the silence becomes too loud to bear?", NULL},			// depression loop PHASE_4
		{NULL}
		};
		
	npc->dialogue.phase_count = sizeof(mother_dialogues) / sizeof(mother_dialogues[0]);
	allocate_dialogues(game, &npc->dialogue, mother_dialogues, npc->dialogue.phase_count);
}

void	spawn_mother(t_game *game, double x, double y)
{
	t_npc		*npc;
	t_dpoint	pos;

	npc = x_calloc(game, 1, sizeof(t_npc));
	pos = (t_dpoint){x, y};
	npc->type = "mother";
	npc->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};

	load_single_texture(game, &npc->texture_idle, MOTHER);
	load_single_texture(game, &npc->texture_blurry, MOTHER_BLURRY);

	init_mother_dialogues(game, npc);
	update_npc_list(game, npc);
}

