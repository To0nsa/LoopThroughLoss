/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_mother.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:23:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/31 11:26:19 by ahavu            ###   ########.fr       */
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
		{"Good morning, dear.",										// denial loop, first iteration PHASE_0
			"I'm still at the hospital. You can call me.", 
			"...", NULL },
		{"I will come through that door, don't worry..."
		"...any moment now.", NULL },								// denial loop, other iterations PHASE_1
		{"...",
			"You should have taken me to the doctor earlier.",
			"Those damn doctors didn't know what they were doing!", NULL }, 		// anger loop PHASE_2
		{"If you'd visited me more often, you would have noticed...",
		"...a sign that something was wrong.", NULL }, 										// bargaining loop PHASE_3
		{"What is your life going to look like...",
			"...without me in it?", NULL},								// depression loop PHASE_4
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

