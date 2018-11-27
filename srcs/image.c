/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:53:56 by lfatton           #+#    #+#             */
/*   Updated: 2018/11/26 17:57:33 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			create_image(t_env *e)
{
 	SDL_SetRenderDrawColor(e->render, 0, 0, 0, 255);
 	SDL_RenderClear(e->render);
	SDL_RenderPresent(e->render);
}

static void		*threading(t_thrds *wolf_thrds)
{
	int		x;
	int		y;

	y = WIN_H / THREADS * wolf_thrds->i;
	while (y < WIN_H / THREADS * (wolf_thrds->i + 1))
	{
		x = 0;
		while (x < WIN_W)
		{
			//fract_thrds->e->fract_funct(fract_thrds->e, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

void			print_image(t_env *e)
{
	pthread_t       thrds[THREADS];
	t_thrds         wolf_thrds[THREADS];
	int                     i;

	i = 0;
	while (i < THREADS)
	{
		wolf_thrds[i].i = i;
		wolf_thrds[i].e = e;
		if (pthread_create(&thrds[i], NULL, (void*)threading, &wolf_thrds[i]))
			error_wolf("cannot create thread");
		i++;
	}
	while (i--)
		if (pthread_join(thrds[i], NULL))
			error_wolf("cannot join threads");
}
