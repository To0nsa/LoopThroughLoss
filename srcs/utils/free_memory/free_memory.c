/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:03:48 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 00:14:59 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static void free_map(t_map *map)
{
	ft_free_array((void **)map->file_content);
	ft_free_array((void **)map->map_layout);
	ft_free_matrix(map->matrix, map->size.y);
	free(map);
}

static void free_textures(t_game *game)
{
	UnloadTexture(game->tex.walls_denial.texture);
	UnloadTexture(game->tex.door_denial.texture);
	UnloadTexture(game->tex.frame_denial.texture);
	UnloadTexture(game->tex.walls_angry.texture);
	UnloadTexture(game->tex.door_angry.texture);
	UnloadTexture(game->tex.frame_angry.texture);
	UnloadTexture(game->tex.walls_acceptance.texture);
	UnloadTexture(game->tex.door_acceptance.texture);
	UnloadTexture(game->tex.frame_acceptance.texture);
	UnloadTexture(game->tex.walls_bargaining.texture);
	UnloadTexture(game->tex.door_bargaining.texture);
	UnloadTexture(game->tex.frame_bargaining.texture);
	UnloadTexture(game->tex.frame_bargaining_repaired.texture);
	UnloadTexture(game->tex.walls_sad.texture);
	UnloadTexture(game->tex.door_sad.texture);
	UnloadTexture(game->tex.frame_sad.texture);
}

static void free_fonts(t_game *game)
{
	UnloadFont(game->font.dialogue);
	UnloadFont(game->font.interaction);
}

static void free_music(t_game *game)
{
	UnloadMusicStream(game->music.voice_message_one.music);
	UnloadMusicStream(game->music.voice_message_two.music);
	UnloadMusicStream(game->music.denial.music);
	UnloadMusicStream(game->music.acceptance.music);
	UnloadMusicStream(game->music.bargaining.music);
	UnloadMusicStream(game->music.anger.music);
	UnloadMusicStream(game->music.depression.music);
	CloseAudioDevice();
}

static void free_single_item(t_item *item)
{
	if (!item)
		return;
	if (item->texture.texture.id > 0)
		UnloadTexture(item->texture.texture);
	if (item->has_message && item->texture_message.texture.id > 0)
		UnloadTexture(item->texture_message.texture);
	if (item->is_broken && item->texture_broken.texture.id > 0)
		UnloadTexture(item->texture_broken.texture);
	free(item->type);
	free(item->name);
	free(item);
}

static void free_items(t_game *game)
{
	for (int i = 0; i < game->item_count; i++)
		free_single_item(game->items[i]);
	free(game->items);
}

static void free_dialogues(t_dial *dialog)
{
	for (int i = 0; i < dialog->phase_count; i++)
		ft_free_array((void **)dialog->dialogues[i]);
	free(dialog->dialogues);
	free(dialog->count);
}

static void free_single_npc(t_npc *npc)
{
	if (!npc)
		return;
	if (npc->texture_idle.texture.id > 0)
		UnloadTexture(npc->texture_idle.texture);
	if (npc->texture_blurry.texture.id > 0)
		UnloadTexture(npc->texture_blurry.texture);
	if (npc->sprite.idle_frames)
	{
		for (int i = 0; i < npc->sprite.idle_frames_count; i++)
			if (npc->sprite.idle_frames[i].texture.id > 0)
				UnloadTexture(npc->sprite.idle_frames[i].texture);
		free(npc->sprite.idle_frames);
	}
	free_dialogues(&npc->dialogue);
	free(npc);
}

static void free_npcs(t_game *game)
{
	for (int i = 0; i < game->npc_count; i++)
		free_single_npc(game->npcs[i]);
	free(game->npcs);
}

static void free_doors(t_game *game)
{
	for (int i = 0; i < game->door_count; i++)
		free(game->doors[i]);
	free(game->doors);
}

void free_game(t_game *game)
{
	if (!game)
		return;
	free_npcs(game);
	free_items(game);
	free_doors(game);
	free(game->entities);
	free_map(game->map);
	free_textures(game);
	free_fonts(game);
	free_music(game);
	CloseWindow();
	free(game);
}
