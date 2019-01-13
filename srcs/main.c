/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:47:49 by lfatton           #+#    #+#             */
/*   Updated: 2018/12/03 18:49:14 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		events_loop(t_env *e)
{
	SDL_Event	event;

	while (!e->quit)
		while (SDL_WaitEvent(&event))
			if ((event.type == SDL_QUIT || event.key.keysym.scancode
						== SDL_SCANCODE_ESCAPE) && (e->quit = 1))
				quit_wolf(e);
}

int			main(int ac, char **av)
{
	t_env	*e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		error_wolf("error: cannot allocate memory");
	if (!(e->cam = (t_cam*)malloc(sizeof(t_cam))))
		error_wolf("error: cannot allocate memory");
	if (ac > 2)
		error_wolf("usage: ./wolf3d or ./wolf3d input_file to "
			"override textures and map with your own");
	if (!(e->sprites = get_sprites(ac - 1, av, e)))
	    error_wolf("There was an issue while loading the bmp.");
	init_wolf(e);
	events_loop(e);
	pthread_exit(NULL);
	return (EXIT_SUCCESS);
}
