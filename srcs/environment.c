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
	mlx_destroy_image(e->mlx_ptr, e->img->ptr);
	mlx_destroy_window(e->mlx_ptr, e->win_ptr);
	free(e->p);
	free(e->img);
	free(e);
	exit(EXIT_SUCCESS);
	return (0);
}

void	init_wolf(t_env *e)
{
	e->mlx_ptr = mlx_init();
	e->win_ptr = mlx_new_window(e->mlx_ptr, WIN_W, WIN_H, "Wolf3D");
	mlx_do_key_autorepeaton(e->mlx_ptr);
	create_image(e);
}
