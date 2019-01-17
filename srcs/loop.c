/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:48:18 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/17 13:48:43 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void treat_events(t_env *e, SDL_Event ev)
{

    if ((ev.type == SDL_QUIT || ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        && (e->quit = 1))
        quit_wolf(e);
    if (ev.type == SDL_MOUSEMOTION)
        e->p->vis -= ev.motion.xrel;
    if (ev.type == SDL_KEYDOWN && ev.key.keysym.scancode == SDL_SCANCODE_LEFT)
        e->p->vis += ROT;
    if (ev.type == SDL_KEYDOWN && ev.key.keysym.scancode == SDL_SCANCODE_RIGHT)
        e->p->vis -= ROT;
    if (ev.type == SDL_KEYDOWN && (ev.key.keysym.scancode == SDL_SCANCODE_W
        || ev.key.keysym.scancode == SDL_SCANCODE_UP || ev.key.keysym.scancode
            == SDL_SCANCODE_S || ev.key.keysym.scancode == SDL_SCANCODE_DOWN
                || ev.key.keysym.scancode == SDL_SCANCODE_A
                    || ev.key.keysym.scancode == SDL_SCANCODE_D))
        move(e, ev.key.keysym.scancode);
    if (ev.key.keysym.scancode == SDL_SCANCODE_LSHIFT || ev.key.keysym.scancode
        == SDL_SCANCODE_F)
        crouch_and_fly(e, ev.type, ev.key.keysym.scancode);
}

void        loop_wolf(t_env *e)
{
    SDL_Event ev;

    while (!e->quit)
    {
        raycasting(e);
        print_image(e);
        while (SDL_PollEvent(&ev))
            treat_events(e, ev);
    }
}