/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:48:18 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/17 19:50:38 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	loop_events(t_env *e, const Uint8 *state)
{
	SDL_Event	ev;

	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE])
			quit_wolf(e);
		if (ev.type == SDL_MOUSEMOTION)
			e->p->vis -= ev.motion.xrel * MOUSE_SENSI;
		if (state[SDL_SCANCODE_LEFT])
			e->p->vis += ROT;
		if (state[SDL_SCANCODE_RIGHT])
			e->p->vis -= ROT;
	}
}

void		loop_wolf(t_env *e)
{
	const Uint8	*state;

	state = SDL_GetKeyboardState(NULL);
	while (42)
	{
		raycasting(e);
		print_image(e);
		loop_events(e, state);
		move(e, state);
		crouch_or_fly(e, state);
	}
}
