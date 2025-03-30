/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_mother.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:23:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 14:23:04 by nlouis           ###   ########.fr       */
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
	dialog->dialogue_count = x_malloc(game, phase_count * sizeof(int));
	while (i < phase_count)
	{
		count = 0;
		while (dialogues[i][count])
			count++;
		dialog->dialogues[i] = x_malloc(game, (count + 1) * sizeof(char *));
		if (!dialog->dialogues[i])
			return ;
		dialog->dialogue_count[i] = count;
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
		{"Oh, you're up early today. That's nice.",										// denial loop, first iteration PHASE_0
			"Why that face? Did you have a bad dream?", 
			"...", NULL },
		{"It's such a peaceful morning, isn't it?", NULL },								// denial loop, other iterations PHASE_1
		{"...",
			"I hear how upset you are… and you have every right to be.",
			"I wish I could take back all the pain, but it's not that simple.",
			"I'm sorry I couldn't be there the way you needed me to be.", NULL }, 		// anger loop PHASE_2
		{"Are you feeling better now?", NULL }, 										// bargaining loop PHASE_3
		{"Your mother is speaking to you...",
			"but you are not able to understand...", NULL},								// depression loop PHASE_4
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
	load_single_xpm(game, &npc->texture_idle, MOTHER, game->mlx);
	load_single_xpm(game, &npc->texture_blurry, MOTHER_BLURRY, game->mlx);
	init_mother_dialogues(game, npc);
	update_npc_list(game, npc);
}
