/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 23:54:09 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/10 14:48:57 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_line(t_env *e)
{
	while (e->y < e->end)
	{
		e->pix[e->x + e->y * WIN_W] = e->color;
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
	if (e->y < 0)
      		e->y = 0;
      	if (e->end >= WIN_H)
      		e->end = WIN_H - 1;
	if (e->hori && e->r->ang > EAST && e->r->ang < WEST)
		e->color = LIGHTGRAY;
	else if (!e->hori && (e->r->ang < NORTH || e->r->ang > SOUTH))
		e->color = SILVER;
	else if (e->hori && e->r->ang >=  WEST)
		e->color = DARKGRAY;
	else if (!e->hori && e->r->ang >= NORTH && e->r->ang <= SOUTH)
		e->color = GRAY;
	draw_line(e);
}

void	print_image(t_env *e)
{
	e->text = SDL_CreateTexture(e->render,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               WIN_W, WIN_H);
	SDL_UpdateTexture(e->text, NULL, e->pix, WIN_W * sizeof (int));
	SDL_RenderClear(e->render);
	SDL_RenderCopy(e->render, e->text, NULL, NULL);
	SDL_RenderPresent(e->render);
}
