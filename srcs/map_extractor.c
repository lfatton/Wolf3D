/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extractor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:32:16 by mtorsell          #+#    #+#             */
/*   Updated: 2019/01/17 23:32:21 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static Uint32		*pointer_to_pixel(int x, int y, Uint32 *pixels)
{
	return (pixels + (x + (y * MAP_W)));
}

static enum e_tile	tiles_fr_px(Uint32 *pixel, SDL_PixelFormat *format)
{
	Uint8	red;
	Uint8	green;
	Uint8	blue;

	red = (double)(*pixel & format->Rmask) / format->Rmask * 255;
	green = (double)(*pixel & format->Gmask) / format->Gmask * 255;
	blue = (double)(*pixel & format->Bmask) / format->Bmask * 255;
	if (red == 255 && green == 255 && blue == 255)
		return (t_wall);
	else if (red == 255 && green == 0 && blue == 0)
		return (t_p_spawn);
	return (t_nil);
}

enum e_tile			**transform_pixels_to_tiles(SDL_Surface *map)
{
	enum e_tile	**til;
	int			i;
	int			y;
	int			x;

	if (!(til = (enum e_tile**)malloc(sizeof(enum e_tile *) * MAP_H)))
		return (NULL);
	i = 0;
	while (i < MAP_H)
	{
		if (!(til[i] = (enum e_tile*)malloc(sizeof(enum e_tile) * MAP_W)))
			return (NULL);
		i++;
	}
	y = -1;
	while (++y < MAP_H)
	{
		x = -1;
		while (++x < MAP_W)
		{
			til[y][x] = tiles_fr_px(
					pointer_to_pixel(x, y, (Uint32*)map->pixels), map->format);
		}
	}
	return (til);
}
