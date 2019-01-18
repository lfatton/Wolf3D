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
	if (e->til[e->map_pos.y][e->map_pos.x])
	{
		e->p->pos.x = e->test.x;
		e->p->pos.y = e->test.y;
	}
}

void		move(t_env *e, const Uint8 *state)
{
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
	{
		e->test.x = e->p->pos.x + cos(ft_degtorad(e->p->vis)) * RUN;
		e->test.y = e->p->pos.y - sin(ft_degtorad(e->p->vis)) * RUN;
	}
	else if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
	{
		e->test.x = e->p->pos.x - cos(ft_degtorad(e->p->vis)) * RUN;
		e->test.y = e->p->pos.y + sin(ft_degtorad(e->p->vis)) * RUN;
	}
	move_if_allowed(e);
	if (state[SDL_SCANCODE_A])
	{
		e->test.x = e->p->pos.x + cos(ft_degtorad(e->p->vis + 90)) * STRAFF;
		e->test.y = e->p->pos.y - sin(ft_degtorad(e->p->vis + 90)) * STRAFF;
	}
	else if (state[SDL_SCANCODE_D])
	{
		e->test.x = e->p->pos.x - cos(ft_degtorad(e->p->vis + 90)) * STRAFF;
		e->test.y = e->p->pos.y + sin(ft_degtorad(e->p->vis + 90)) * STRAFF;
	}
	move_if_allowed(e);
}

void		crouch_or_fly(t_env *e, const Uint8 *state)
{
	if (state[SDL_SCANCODE_C])
		e->p->height = WIN_H - 2 * WIN_H / 3;
	else if (state[SDL_SCANCODE_F])
		e->p->height = WIN_H - WIN_H / 3;
	else if (!state[SDL_SCANCODE_C] && !state[SDL_SCANCODE_F])
		e->p->height = HALF_H;
}
