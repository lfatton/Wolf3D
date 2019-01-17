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

static void	move_if_allowed(t_env *e)
{
    e->map_pos.x = e->test.x / (int)TILE;
    e->map_pos.y = e->test.y / (int)TILE;
    if (e->tiles[e->map_pos.y][e->map_pos.x])
    {
        e->p->pos.x = e->test.x;
        e->p->pos.y = e->test.y;
    }
}

void		move(t_env *e, Uint8 key)
{
	if (key == SDL_SCANCODE_W || key == SDL_SCANCODE_UP)
	{
		e->test.x = e->p->pos.x + cos(ft_degtorad(e->p->vis)) * SPEED;
		e->test.y = e->p->pos.y - sin(ft_degtorad(e->p->vis)) * SPEED;
	}
	else if (key == SDL_SCANCODE_S || key == SDL_SCANCODE_DOWN)
	{
		e->test.x = e->p->pos.x - cos(ft_degtorad(e->p->vis)) * SPEED;
		e->test.y = e->p->pos.y + sin(ft_degtorad(e->p->vis)) * SPEED;
	}
	else if (key == SDL_SCANCODE_A)
	{
		e->test.x = e->p->pos.x + cos(ft_degtorad(e->p->vis + 90)) * SPEED;
		e->test.y = e->p->pos.y - sin(ft_degtorad(e->p->vis + 90)) * SPEED;
	}
	else if (key == SDL_SCANCODE_D)
	{
		e->test.x = e->p->pos.x - cos(ft_degtorad(e->p->vis + 90)) * SPEED;
		e->test.y = e->p->pos.y + sin(ft_degtorad(e->p->vis + 90)) * SPEED;
	}
	move_if_allowed(e);
}

void		crouch_and_fly(t_env *e, Uint32 type, Uint8 key)
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
