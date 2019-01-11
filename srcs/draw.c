/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 23:54:09 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/11 14:38:32 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

Uint32	get_pixel(SDL_Surface *s, int x, int y) 
{
	Uint32	*pix;

	pix = (Uint32*)s->pixels;
	return (pix[x + y * s->w]);
} 

void	put_pixel(SDL_Surface *s, int x, int y, Uint32 color)
{
	Uint32	*pix;

	pix = (Uint32*)s->pixels;
	pix[x + y * s->w] = color;
}

void	draw_line(t_env *e)
{
	double y;

	y = TILE / 2;
	while (e->y < e->end)
	{
		//put_pixel(e->surf, e->x, e->y, get_pixel(e->wall, e->r->offset, y));
		put_pixel(e->surf, e->x, e->y, e->color);
		/*if (y > TILE - 1)
			y = TILE - 1;
		y += TILE / e->r->length;*/
		e->y++;
	}
}

void	draw_ceil_and_floor(t_env *e)
{
	e->y = 0;
	e->end = HALF_H;
	e->color = SKYBLUE;
	draw_line(e);
	e->y = HALF_H;
	e->end = WIN_H - 1;
	e->color = BROWN;
	draw_line(e);
}

void	draw(t_env *e)
{
	e->r->dist *= cos(ft_degtorad(e->p->vis - e->r->ang));
      	e->r->length = RATIO / e->r->dist;
	draw_ceil_and_floor(e);
      	e->y = HALF_H - e->r->length / 2;
      	e->end = e->r->length + e->y;
	e->y = (e->y < 0 ? 0 : e->y);
	e->end = (e->end >= WIN_H ? WIN_H - 1 : e->end);
	if (e->hori)
	{
		e->r->offset = fmod(e->r->h_hit_x, TILE);
		if (e->r->ang > EAST && e->r->ang < WEST)
			e->color = LIGHTGRAY;
		else
			e->color = DARKGRAY;
	}
	else
	{
		e->r->offset = fmod(e->r->v_hit_y, TILE);
		if (e->r->ang >= NORTH && e->r->ang <= SOUTH)
			e->color = GRAY;
		else
			e->color = SILVER;
	}
	//e->color = get_pixel(e->wall, e->r->offset, e->y);
	draw_line(e);
}

void	print_image(t_env *e)
{
	SDL_DestroyTexture(e->text);
	SDL_RenderClear(e->render);
	if (!(e->text = SDL_CreateTextureFromSurface(e->render, e->surf)))
		error_wolf("error: cannot create texture");
	SDL_RenderCopy(e->render, e->text, NULL, NULL);
	SDL_RenderPresent(e->render);
}
