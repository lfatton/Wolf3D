/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 23:54:09 by lfatton           #+#    #+#             */
/*   Updated: 2019/02/05 16:41:42 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_wall(t_env *e)
{
	if (e->spr->wall == e->spr->w_s || e->spr->wall
			== e->spr->w_w)
		e->r->text.x = WALL_RES - e->r->text.x;
	while (e->start < e->end)
	{
		e->r->text.y = (e->start - e->p->height + e->r->length / 2)
			* WALL_RES / e->r->length;
		e->color = get_pixel(e->spr->wall, e->r->text.x, e->r->text.y);
		put_pixel(e->surf, e->col, e->start, e->color);
		e->start++;
	}
}

static void	draw_ceil_and_floor(t_env *e)
{
	e->start = 0;
	e->end = e->p->height;
	e->color = SKYBLUE;
	while (e->start < e->end)
	{
		put_pixel(e->surf, e->col, e->start, e->color);
		e->start++;
	}
	e->start = e->p->height;
	e->end = WIN_H - 1;
	e->color = BROWN;
	while (e->start < e->end)
	{
		put_pixel(e->surf, e->col, e->start, e->color);
		e->start++;
	}
}

void		draw(t_env *e)
{
	e->r->dist *= cos(ft_degtorad(e->p->vis - e->r->ang));
	e->r->length = RATIO / e->r->dist;
	draw_ceil_and_floor(e);
	e->start = e->p->height - e->r->length / 2 + 1;
	e->end = e->p->height + e->r->length / 2;
	e->start = (e->start < 0 ? 0 : e->start);
	e->end = (e->end >= WIN_H ? WIN_H - 1 : e->end);
	if (e->hori)
	{
		e->r->text.x = fmod(e->r->h_hit_x, TILE);
		if (e->r->ang > EAST && e->r->ang < WEST)
			e->spr->wall = e->spr->w_n;
		else
			e->spr->wall = e->spr->w_s;
	}
	else
	{
		e->r->text.x = fmod(e->r->v_hit_y, TILE);
		if (e->r->ang >= NORTH && e->r->ang <= SOUTH)
			e->spr->wall = e->spr->w_w;
		else
			e->spr->wall = e->spr->w_e;
	}
	draw_wall(e);
}
