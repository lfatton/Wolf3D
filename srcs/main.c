/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:47:49 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/11 13:08:22 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			main(int ac, char **av)
{
	t_env	*e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		error_wolf("error: cannot allocate memory for struct env");
	if (ac > 2)
		error_wolf("usage: ./wolf3d or ./wolf3d input_file to "
			"override textures and map with your own");
	if (!(e->spr = get_sprites(ac - 1, av, e)))
		error_wolf("There was an issue while loading the bmp.");
	if (!(e->p = (t_player*)malloc(sizeof(t_player))))
		error_wolf("error: cannot allocate memory for struct player");
	if (!(e->r = (t_ray*)malloc(sizeof(t_ray))))
		error_wolf("error: cannot allocate memory for struct ray");
	init_wolf(e);
	loop_wolf(e);
	return (EXIT_SUCCESS);
}
