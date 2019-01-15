#include "wolf3d.h"

static Uint32		*pointer_to_pixel(int x, int y, Uint32 *pixels)
{
	return (pixels + (x + (y * MAP_W)));
}

static enum TTile		transform_pixel_to_tile(Uint32 *pixel, SDL_PixelFormat *format)
{
	int red;
	Uint8 green;
	Uint8 blue;

	red = (double)(*pixel & format->Rmask) / format->Rmask * 255;
	green = (double)(*pixel & format->Gmask) / format->Gmask * 255;
	blue = (double)(*pixel & format->Bmask) / format->Bmask * 255;

	if (red == 255 && green == 255 && blue == 255)
		return (tWall);
	else if (red == 255 && green == 0 && blue == 0)
		return (tPlayerSpawn);
	return (tEmpty);
}

enum TTile			**transform_pixels_to_tiles(SDL_Surface *map)
{
	enum TTile	**tiles;
	int			i;
	int			y;
	int			x;

	if (!(tiles = (enum TTile**)malloc(sizeof(enum TTile *) * MAP_H)))
		return NULL;
	i = 0;
	while (i < MAP_H) {
		if (!(tiles[i] = (enum TTile*)malloc(sizeof(enum TTile) * MAP_W)))
			return NULL;
		i++;
	}
	y = -1;
	while (++y < MAP_H)
	{
		x = -1;
		while (++x < MAP_W) {
			tiles[y][x] = transform_pixel_to_tile(
					pointer_to_pixel(x, y, (Uint32*)map->pixels), map->format);
		}
	}
	return (tiles);
}

SDL_Surface		*extract_map(SDL_Surface *all)
{
	SDL_Surface		*map;
	Uint32			*pixels;
	int 			x;
	int				y;

	if (!(map = SDL_CreateRGBSurfaceWithFormat(0, MAP_W, MAP_H, 32, all->format->format)))
		return NULL;
	pixels = (Uint32 *)all->pixels;
	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W)
		{
			((Uint32 *)map->pixels)[x + (y * MAP_W)] = pixels[x + (y * MAP_W)];
			x++;
		}
		y++;
	}
	return (map);
}

/*
void				read_tiles(t_env *e)
{
	int x, y = 0;

	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W)
		{
			if (e->tiles[y][x] == tWall)
				ft_putchar('w');
			else if (e->tiles[y][x] == tEmpty)
				ft_putchar('e');
			else if (e->tiles[y][x] == tPlayerSpawn)
				ft_putchar('p');
			ft_putchar(' ');
			x++;
		}
		ft_putendl("");
		y++;
	}
}
*/
