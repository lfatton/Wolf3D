/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:08:55 by mtorsell          #+#    #+#             */
/*   Updated: 2019/02/05 16:47:02 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface			*cpy_fr_surf(SDL_Surface *src, t_coords from, t_coords size)
{
	SDL_Surface		*new;
	Uint32			*pixels;
	int				x;
	int				y;

	if (from.x + size.x > src->w || from.y + size.y > src->h)
		return (NULL);
	if (!(new = SDL_CreateRGBSurfaceWithFormat(0,
			size.x, size.y, 32, src->format->format)))
		error_wolf("There was an issue while creating a surface");
	pixels = (Uint32 *)src->pixels;
	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			((Uint32 *)new->pixels)[x + (y
				* size.x)] = pixels[(from.x + x) + ((from.y + y) * src->w)];
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
	dimensions.x = WALL_RES;
	dimensions.y = WALL_RES;
	spr->w_n = cpy_fr_surf(spr->all, start, dimensions);
	start.x += WALL_RES;
	spr->w_s = cpy_fr_surf(spr->all, start, dimensions);
	start.x += WALL_RES;
	spr->w_e = cpy_fr_surf(spr->all, start, dimensions);
	start.x += WALL_RES;
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
		error_wolf("There was an issue while allocating memory.");
	if (ac)
		path = av[1];
	if (!(spr->all = SDL_LoadBMP(path)) || spr->all->format->BytesPerPixel < 4)
		error_wolf("It seems your BMP is invalid. It need to be 32bits.");
	if (!(spr->map = cpy_fr_surf(spr->all, start, dimensions)))
		error_wolf("There was an issue with SDL_Surface creation.");
	if (!(e->til = transform_pixels_to_tiles((spr->map))))
		error_wolf("There has been an issue while mallocing for the map.");
	extract_walls(spr);
	if (!spr->w_n || !spr->w_s || !spr->w_e || !spr->w_w)
		error_wolf("There was an issue with SDL_Surface creation.");
	verify_map(e->til);
	return (spr);
}
