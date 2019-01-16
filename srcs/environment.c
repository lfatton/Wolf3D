/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:52:06 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/15 18:17:33 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		error_wolf(char *err)
{
	ft_putendl(err);
	exit(EXIT_FAILURE);
}

void		spawn_player(t_env *e)
{
	e->p->pos.y = 1;
	while (e->p->pos.y < MAP_H - 1)
	{
		e->p->pos.x = 1;
		while (e->p->pos.x < MAP_W - 1)
		{
			if (e->tiles[(int)e->p->pos.y][(int)e->p->pos.x] == tPlayerSpawn)
				return ;
			e->p->pos.x++;
		}
		e->p->pos.y++;
	}
}


int				quit_wolf(t_env *e)
{
	SDL_FreeSurface(e->sprites->wallN);
	SDL_FreeSurface(e->sprites->wallW);
	SDL_FreeSurface(e->sprites->wallS);
	SDL_FreeSurface(e->sprites->wallE);
	SDL_FreeSurface(e->sprites->map);
	SDL_FreeSurface(e->sprites->all);
	SDL_FreeSurface(e->surf);
	SDL_DestroyTexture(e->text);
	SDL_DestroyRenderer(e->render);
	SDL_DestroyWindow(e->win);
	SDL_Quit();
	free(e->p);
	free(e->r);
	free(e->sprites);
	free(e);
	exit(EXIT_SUCCESS);
	return (0);
}

static void	init_player(t_env *e)
{
	e->p->height = HALF_H;
	e->p->vis = 30;
	e->p->crouch = 0;
	e->p->fly = 0;
	spawn_player(e);
	e->tiles[(int)e->p->pos.y][(int)e->p->pos.x] = tEmpty;
	e->p->pos.y *= TILE;
	e->p->pos.x *= TILE;
}

void	init_wolf(t_env *e)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error_wolf("error: cannot run SDL");
	if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, SDL_WINDOW_FULLSCREEN_DESKTOP, &e->win, &e->render) < 0)
		error_wolf("error: cannot create window");
	if (SDL_ShowCursor(SDL_DISABLE) < 0)
		error_wolf("error: cannot hide mouse cursor");
	if (!(e->surf = SDL_CreateRGBSurfaceWithFormat(0, WIN_W, WIN_H, 32, e->sprites->all->format->format)))
		error_wolf("error: cannot create surface");
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
			if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_LEFT)
				e->p->vis += SPEED;
			if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				e->p->vis -= SPEED;
			if (event.type == SDL_KEYDOWN && (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.scancode == SDL_SCANCODE_UP))
				move_up(e);
			if (event.type == SDL_KEYDOWN && (event.key.keysym.scancode == SDL_SCANCODE_S || event.key.keysym.scancode == SDL_SCANCODE_DOWN))
				move_down(e);
			if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_D)
				move_right(e);
			if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_A)
				move_left(e);
			if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT || event.key.keysym.scancode == SDL_SCANCODE_F)
				crouch_and_fly(e, event.key.keysym.scancode, event.type);
		}
	}
}
