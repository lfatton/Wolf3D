/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:52:06 by lfatton           #+#    #+#             */
/*   Updated: 2018/11/26 17:53:48 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	error_wolf(char *err)
{
	ft_putendl(err);
	exit(EXIT_FAILURE);
}

int		quit_wolf(t_env *e)
{
	SDL_DestroyRenderer(e->render);
    	SDL_DestroyWindow(e->win);
	SDL_Quit ();
	free(e->p);
	free(e->img);
	free(e);
	exit(EXIT_SUCCESS);
	return (0);
}

void	init_wolf(t_env *e)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error_wolf("error: cannot run SDL");
	if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0, &e->win, &e->render))
		error_wolf("error: cannot create window");
	create_image(e);
}
