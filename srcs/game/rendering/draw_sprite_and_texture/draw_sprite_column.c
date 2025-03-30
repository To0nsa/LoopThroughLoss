/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_column.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:22:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/30 21:28:26 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

static bool	is_sprite_stripe_visible(t_sprite_draw *data, double *z_buffer)
{
	if (data->transform.y <= 0)
		return (false);
	if (data->stripe_x < 0 || data->stripe_x >= WIN_W)
		return (false);
	if (data->transform.y >= z_buffer[data->stripe_x])
		return (false);
	return (true);
}

/* static int	calc_tex_pixel_x(int stripe_x, int screen_x,
										int sprite_width, int texture_width)
{
	int	relative_x;

	relative_x = stripe_x - (-sprite_width / 2 + screen_x);
	return ((relative_x * texture_width) / sprite_width);
} */

/*
 * This function draws exactly one vertical "stripe" (i.e., 1 pixel wide)
 * of the sprite at screen x = data->stripe_x. We do a custom column approach
 * so we can test each stripe against z_buffer (for Wolf3D‐style wall occlusion).
 *
 * Key points:
 *  1) We figure out how far into the texture we are horizontally (texX).
 *  2) We clamp top/bottom of the on‐screen column to [0..WIN_H],
 *     and skip only that portion in texture space.
 *  3) We draw exactly a 1px‐wide Rectangle in screen coordinates
 *     mapped from a 1px‐wide Rectangle in texture coordinates.
 */
void draw_sprite_column(t_game *game, t_sprite_draw *data, double *z_buffer)
{
	(void)game;
	// If the sprite’s depth or column is hidden behind a closer wall, skip it.
	// (Implement however you want—e.g. compare data->transform.y to z_buffer[data->stripe_x].)
	if (!is_sprite_stripe_visible(data, z_buffer))
		return;

	// We want to see how far we are across the sprite’s width.
	float spriteWidthF  = (float)data->width;
	float textureWidthF = (float)data->texture->size.x;

	// The sprite is centered at data->screen_x with width = data->width,
	// so its left edge in screen coords is (screen_x - width/2).
	float leftEdge = (float)(data->screen_x - data->width / 2);

	// xOffset = how far from the sprite’s left edge (in screen coords).
	float xOffset = (float)data->stripe_x - leftEdge;

	// Fraction across the sprite’s width, in [0..1].
	float fractionX = xOffset / spriteWidthF;

	// Convert that fraction to a texture x coordinate in [0..textureWidth].
	float texX = fractionX * textureWidthF;

	// The raw on‐screen vertical bounds of the sprite:
	int spriteTop    = data->draw_start.y; // could be negative if off‐screen
	int spriteBottom = data->draw_end.y;   // could be > WIN_H if off‐screen

	// The total “intended” column height is:
	int rawColHeight = spriteBottom - spriteTop;
	if (rawColHeight <= 0) return; // sprite collapsed or invalid

	// 1) Clamp the actual on‐screen range to [0..WIN_H‐1].
	int clippedTop = spriteTop;
	if (clippedTop < 0)
		clippedTop = 0;

	int clippedBottom = spriteBottom;
	if (clippedBottom > (WIN_H - 1))
		clippedBottom = (WIN_H - 1);

	int finalColHeight = clippedBottom - clippedTop;
	if (finalColHeight <= 0)
		return; // nothing to draw on‐screen

	// 2) Figure out how many pixels we “skipped” at the top of the sprite
	//    (in screen space). For instance, if spriteTop was ‐10, we skip 10 px.
	int skipTop = clippedTop - spriteTop;

	// 3) Determine how many texture‐pixels correspond to 1 screen‐pixel vertically.
	//    Typically we scale the entire texture->size.y to data->height screen pixels.
	float texPixelsPerScreenPixel = (float)data->texture->size.y / (float)data->height;

	// 4) So for the portion above the screen, we skip that many texture px:
	float srcY      = skipTop * texPixelsPerScreenPixel;
	// For the portion that remains, the final on‐screen height is finalColHeight,
	// so in texture space we cover finalColHeight * texPixelsPerScreenPixel:
	float srcHeight = finalColHeight * texPixelsPerScreenPixel;

	// Build the source rectangle (1 pixel wide in texture).
	Rectangle srcRect = {
		.x = texX,
		.y = srcY,
		.width = 1.0f,
		.height = srcHeight
	};

	// Build the destination rectangle (1 pixel wide on screen).
	Rectangle destRect = {
		.x = (float)data->stripe_x,   // which column on screen
		.y = (float)clippedTop,       // where we start drawing
		.width = 1.0f,                // 1px wide
		.height = (float)finalColHeight
	};

	DrawTexturePro(
		data->texture->texture,  // The Raylib texture
		srcRect,                 // which 1px vertical slice of the texture
		destRect,                // where on screen that slice goes
		(Vector2){0.0f, 0.0f},   // origin offset (top‐left)
		0.0f,                    // rotation
		WHITE                    // tint
	);
}

