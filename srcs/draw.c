/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 23:54:09 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/14 11:28:31 by lfatton          ###   ########.fr       */
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

void	draw_wall(t_env *e)
{
	if (e->sprites->wall == e->sprites->wallS || e->sprites->wall == e->sprites->wallW)
		e->r->text.x = TILE - e->r->text.x;
	while (e->y < e->end)
	{
		e->r->text.y = (e->y - e->p->height + e->r->length / 2) * TILE / e->r->length;
		e->color = get_pixel(e->sprites->wall, e->r->text.x, e->r->text.y);
		put_pixel(e->surf, e->x, e->y, e->color);
		e->y++;
	}
}

void	draw_ceil_and_floor(t_env *e)
{
	e->y = 0;
	e->end = e->p->height;
	e->color = SKYBLUE;
	while (e->y < e->end)
	{
		put_pixel(e->surf, e->x, e->y, e->color);
		e->y++;
	}
	e->y = e->p->height;
	e->end = WIN_H - 1;
	e->color = BROWN;
	while (e->y < e->end)
	{
		put_pixel(e->surf, e->x, e->y, e->color);
		e->y++;
	}
}

void	draw(t_env *e)
{
	e->r->dist *= cos(ft_degtorad(e->p->vis - e->r->ang));
	e->r->length = RATIO / e->r->dist;
	draw_ceil_and_floor(e);
	e->y = e->p->height - e->r->length / 2 + 1;
	e->end = e->p->height + e->r->length / 2;
	e->y = (e->y < 0 ? 0 : e->y);
	e->end = (e->end >= WIN_H ? WIN_H - 1 : e->end);
	if (e->hori)
	{
		e->r->text.x = fmod(e->r->h_hit_x, TILE);
		if (e->r->ang > EAST && e->r->ang < WEST)
			e->sprites->wall = e->sprites->wallN;
		else
			e->sprites->wall = e->sprites->wallS;
	}
	else
	{
		e->r->text.x = fmod(e->r->v_hit_y, TILE);
		if (e->r->ang >= NORTH && e->r->ang <= SOUTH)
			e->sprites->wall = e->sprites->wallW;
		else
			e->sprites->wall = e->sprites->wallE;
	}
	draw_wall(e);
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
