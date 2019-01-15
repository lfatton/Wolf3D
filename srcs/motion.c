/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:27:34 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/14 12:08:28 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_left(t_env *e)
{
	t_coords	test;
	
	test.x = e->p->pos.x + cos(ft_degtorad(e->p->vis + 90)) * SPEED;
	test.y = e->p->pos.y - sin(ft_degtorad(e->p->vis + 90)) * SPEED;
	e->m->x = test.x / (int)TILE;
	e->m->y = test.y / (int)TILE;
	if (!maptest[e->m->y][e->m->x])
	{
		e->p->pos.x = test.x;
		e->p->pos.y = test.y;
	}
}

void	move_right(t_env *e)
{
	t_coords	test;
	
	test.x = e->p->pos.x - cos(ft_degtorad(e->p->vis + 90)) * SPEED;
	test.y = e->p->pos.y + sin(ft_degtorad(e->p->vis + 90)) * SPEED;
	e->m->x = test.x / (int)TILE;
	e->m->y = test.y / (int)TILE;
	if (!maptest[e->m->y][e->m->x])
	{
		e->p->pos.x = test.x;
		e->p->pos.y = test.y;
	}
}

void	move_down(t_env *e)
{
	t_coords	test;
	
	test.x = e->p->pos.x - cos(ft_degtorad(e->p->vis)) * SPEED;
	test.y = e->p->pos.y + sin(ft_degtorad(e->p->vis)) * SPEED;
	e->m->x = test.x / (int)TILE;
	e->m->y = test.y / (int)TILE;
	if (!maptest[e->m->y][e->m->x])
	{
		e->p->pos.x = test.x;
		e->p->pos.y = test.y;
	}
}

void	move_up(t_env *e)
{
	t_coords	test;
	
	test.x = e->p->pos.x + cos(ft_degtorad(e->p->vis)) * SPEED;
	test.y = e->p->pos.y - sin(ft_degtorad(e->p->vis)) * SPEED;
	e->m->x = test.x / (int)TILE;
	e->m->y = test.y / (int)TILE;
	if (!maptest[e->m->y][e->m->x])
	{
		e->p->pos.x = test.x;
		e->p->pos.y = test.y;
	}
}

void	crouch_and_fly(t_env *e, int key, int type)
{
	double	newheight;

	if (key == SDL_SCANCODE_LSHIFT)
		newheight = WIN_H - 2 * WIN_H / 3;
	else if (key == SDL_SCANCODE_F)
		newheight = WIN_H - WIN_H / 3;
	if (type == SDL_KEYDOWN)
		e->p->height = newheight;
	else if (type == SDL_KEYUP)
		e->p->height = HALF_H;
}
