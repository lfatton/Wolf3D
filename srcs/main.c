/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:47:49 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/10 00:08:06 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
				e->p->vis += 5;
			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				e->p->vis -= 5;
		}
	}
}

int			main(int ac, char **av)
{
	int		fd;
	t_env	*e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		error_wolf("error: cannot allocate memory for struct env");
	if (!(e->p = (t_player*)malloc(sizeof(t_player))))
		error_wolf("error: cannot allocate memory for struct player");
	if (!(e->r = (t_ray*)malloc(sizeof(t_ray))))
		error_wolf("error: cannot allocate memory for struct ray");
	if (!(e->m = (t_map*)malloc(sizeof(t_map))))
		error_wolf("error: cannot allocate memory for struct map");
	if (ac != 2)
		error_wolf("usage: ./wolf3d input_file");
	fd = open(av[1], O_RDONLY);
	close(fd);
	init_wolf(e);
	loop_wolf(e);
	return (EXIT_SUCCESS);
}
