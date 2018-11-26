/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:57:43 by lfatton           #+#    #+#             */
/*   Updated: 2018/11/26 18:20:36 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	key_hook(int key, t_env *e)
{
	if (key == ESC)
		quit_wolf(e);
	expose_hook(e);
	return (0);
}

int	mouse_hook(int btn, int x, int y, t_env *e)
{
	x = y;
	btn = x;
	expose_hook(e);
	return (0);
}

int	mouse_motion(int x, int y, t_env *e)
{
	x = y;
	expose_hook(e);
	return (0);
}

int	expose_hook(t_env *e)
{
	mlx_clear_window(e->mlx_ptr, e->win_ptr);
	print_image(e);
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img->ptr, 0, 0);
	return (0);
}
