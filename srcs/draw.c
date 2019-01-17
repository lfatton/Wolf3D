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

static void	draw_wall(t_env *e)
{
	if (e->sprites->wall == e->sprites->wallS || e->sprites->wall
		== e->sprites->wallW)
		e->r->text.x = TILE - e->r->text.x;
	while (e->start < e->end)
	{
		e->r->text.y = (e->start - e->p->height + e->r->length / 2)
				* TILE / e->r->length;
		e->color = get_pixel(e->sprites->wall, e->r->text.x, e->r->text.y);
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
