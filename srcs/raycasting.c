/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:01:55 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/10 16:24:24 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	dda(t_env *e)
{
	e->m->x = e->r->hit.x / (int)TILE;
	e->m->y = e->r->hit.y / (int)TILE;
	while (e->m->x > 0 && e->m->y > 0 && e->m->x < e->m->w && e->m->y < e->m->h && !maptest[e->m->y][e->m->x])
	{
		e->r->hit.x += e->r->step.x;
		e->r->hit.y += e->r->step.y;
		e->m->x = e->r->hit.x / (int)TILE;
		e->m->y = e->r->hit.y / (int)TILE;
	}
}

static double	raycast_ver(t_env *e)
{
	e->r->tan = tan(ft_degtorad(e->r->ang));
	if (e->r->ang < NORTH || e->r->ang > SOUTH)
	{
		e->r->step.x = TILE;
		e->r->hit.x = floor(e->p->pos.x / TILE) * TILE + TILE;
	}
	else
	{
		e->r->step.x = -TILE;
		e->r->hit.x = floor(e->p->pos.x / TILE) * TILE - 0.001;
	}
	e->r->hit.y = e->p->pos.y + (e->p->pos.x - e->r->hit.x) * e->r->tan;
	if (e->r->ang == EAST || e->r->ang == WEST)
		e->r->step.y = 0;
	else
		e->r->step.y = TILE * -e->r->tan;
	if (e->r->ang >= NORTH && e->r->ang <= SOUTH)
		e->r->step.y = -e->r->step.y;
	dda(e);
	return (sqrt(ft_sq((e->p->pos.x - e->r->hit.x)) + ft_sq((e->p->pos.y - e->r->hit.y))));
}

static double	raycast_hor(t_env *e)
{
	e->r->tan = tan(ft_degtorad(e->r->ang));
	if (e->r->ang > EAST && e->r->ang < WEST)
	{
		e->r->step.y = -TILE;
		e->r->hit.y = floor(e->p->pos.y / TILE) * TILE - 0.001;
	}
	else
	{
		e->r->step.y = TILE;
		e->r->hit.y = floor(e->p->pos.y / TILE) * TILE + TILE;
	}
	e->r->hit.x = e->p->pos.x + (e->p->pos.y - e->r->hit.y) / e->r->tan;
	if (e->r->ang == NORTH || e->r->ang == SOUTH)
		e->r->step.x = 0;
	else
		e->r->step.x = TILE / e->r->tan;
	if (e->r->ang > WEST)
		e->r->step.x = -e->r->step.x;
	dda(e);
	return (sqrt(ft_sq((e->p->pos.x - e->r->hit.x)) + ft_sq((e->p->pos.y - e->r->hit.y))));
}

void	raycasting(t_env *e)
{
	double	h_res;
	double	v_res;

	e->x = 0;
	e->r->ang = e->p->vis + FOV / 2;
	while (e->x < WIN_W)
	{
		e->hori = 0;
		e->r->ang += (e->r->ang < 0) ? 360 : 0;
		e->r->ang -= (e->r->ang >= 360) ? 360 : 0;
		h_res = raycast_hor(e);
		e->r->h_hit_x = e->r->hit.x;
		v_res = raycast_ver(e);
		e->r->v_hit_y = e->r->hit.y;
		if ((h_res < v_res) && (e->hori = 1))
			e->r->dist = h_res;
		else
			e->r->dist = v_res;
		draw(e);
		e->r->ang -= DECR_ANG;
		e->x++;
	}
}
