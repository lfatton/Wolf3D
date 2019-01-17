/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:08:55 by mtorsell          #+#    #+#             */
/*   Updated: 2019/01/17 23:19:10 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface			*cpy_fr_surf(SDL_Surface *src, t_coords from, t_coords size)
{
	SDL_Surface		*new;
	Uint32			*pixels;
	int				x;
	int				y;

	if (!(new = SDL_CreateRGBSurfaceWithFormat(0,
			size.x, size.y, 32, src->format->format)))
		return (NULL);
	pixels = (Uint32 *)src->pixels;
	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			((Uint32 *)new->pixels)[x + (y * size.x)] =
					pixels[(from.x + x) + ((from.y + y) * src->w)];
			x++;
		}
		y++;
	}
	return (new);
}

void				extract_walls(t_sprites *spr)
{
	t_coords		start;
	t_coords		dimensions;

	start.x = 0;
	start.y = MAP_H;
	dimensions.x = TILE;
	dimensions.y = TILE;
	spr->w_n = cpy_fr_surf(spr->all, start, dimensions);
	start.x += TILE;
	spr->w_s = cpy_fr_surf(spr->all, start, dimensions);
	start.x += TILE;
	spr->w_e = cpy_fr_surf(spr->all, start, dimensions);
	start.x += TILE;
	spr->w_w = cpy_fr_surf(spr->all, start, dimensions);
}

t_sprites			*get_sprites(int ac, char **av, t_env *e)
{
	char		*path;
	t_sprites	*spr;
	t_coords	start;
	t_coords	dimensions;

	start.x = 0;
	start.y = 0;
	dimensions.x = MAP_W;
	dimensions.y = MAP_H;
	path = BMP_PATH;
	if (!(spr = (t_sprites*)malloc(sizeof(t_sprites))))
		return (NULL);
	if (ac)
		path = av[1];
	if (!(spr->all = SDL_LoadBMP(path)))
		return (NULL);
	if (!(spr->map = cpy_fr_surf(spr->all, start, dimensions)))
		return (NULL);
	if (!(e->til = transform_pixels_to_tiles((spr->map))))
		return (NULL);
	extract_walls(spr);
	if (!spr->w_n || !spr->w_s || !spr->w_e || !spr->w_w)
		return (NULL);
	verify_map(e->til);
	return (spr);
}
