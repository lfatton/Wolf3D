/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:52:06 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/10 16:06:44 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		error_wolf(char *err)
{
	ft_putendl(err);
	exit(EXIT_FAILURE);
}

int			quit_wolf(t_env *e)
{
	SDL_DestroyRenderer(e->render);
	SDL_DestroyWindow(e->win);
	SDL_Quit();
	free(e->p);
	free(e->r);
	free(e->m);
	free(e);
	exit(EXIT_SUCCESS);
	return (0);
}

static void	init_player(t_env *e)
{
	//e->p->height = TILE / 2;
	e->p->pos.x = 2 * TILE;
	e->p->pos.y = 2 * TILE;
	e->p->vis = 30;
e->m->w = 24;
e->m->h = 24;
}

void	init_wolf(t_env *e)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error_wolf("error: cannot run SDL");
	if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0, &e->win, &e->render))
		error_wolf("error: cannot create window");
	if (!(e->pix = (int*)malloc(sizeof(int) * WIN_W * WIN_H)))
		error_wolf("error: cannot allocate memory for the image");
	e->quit = 0;
	init_player(e);
}

void		loop_wolf(t_env *e)
{
	SDL_Event	event;

	while (!e->quit)
	{
		raycasting(e);
		print_image(e);
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) && (e->quit = 1))
				quit_wolf(e);
			if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
				e->p->vis += SPEED;
			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				e->p->vis -= SPEED;
			if (event.key.keysym.scancode == SDL_SCANCODE_W)
				move_up(e);
			if (event.key.keysym.scancode == SDL_SCANCODE_S)
				move_down(e);
			if (event.key.keysym.scancode == SDL_SCANCODE_D)
				move_right(e);
			if (event.key.keysym.scancode == SDL_SCANCODE_A)
				move_left(e);
		}
	}
}
