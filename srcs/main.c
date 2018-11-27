/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:47:49 by lfatton           #+#    #+#             */
/*   Updated: 2018/11/26 18:17:44 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		events_loop(t_env *e)
{
	SDL_Event	event;

	while (1)
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				quit_wolf(e);
}

int			main(int ac, char **av)
{
	int		fd;
	t_env	*e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		error_wolf("error: cannot allocate memory");
	if (!(e->img = (t_img*)malloc(sizeof(t_img))))
		error_wolf("error: cannot allocate memory");
	if (!(e->p = (t_point*)malloc(sizeof(t_point))))
		error_wolf("error: cannot allocate memory");
	if (ac != 2)
		error_wolf("usage: ./wolf3d input_file");
	fd = open(av[1], O_RDONLY);
	parse(e, fd);
	close(fd);
	init_wolf(e);
	events_loop(e);
	pthread_exit(NULL);
	return (EXIT_SUCCESS);
}
