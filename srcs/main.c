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

int			main(int ac, char **av)
{
	int		fd;
	t_env	*e;

	e = (t_env*)malloc(sizeof(t_env));
	e->img = (t_img*)malloc(sizeof(t_img));
	e->p = (t_point*)malloc(sizeof(t_point));
	if (ac != 2)
		error_wolf("usage: ./wolf3d input_file");
	fd = open(av[1], O_RDONLY);
	parse(e, fd);
	close(fd);
	init_wolf(e);
//	mlx_expose_hook(e->win_ptr, expose_hook, e);
//	mlx_hook(e->win_ptr, 2, 5, key_hook, e);
//	mlx_hook(e->win_ptr, 4, 1L << 2, mouse_hook, e);
//	mlx_hook(e->win_ptr, 6, 1L << 6, mouse_motion, e);
//	mlx_hook(e->win_ptr, 17, 1L << 17, quit_wolf, e);
//	mlx_loop(e->mlx_ptr);
	pthread_exit(NULL);
	return (EXIT_SUCCESS);
}
