/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:37:43 by lfatton           #+#    #+#             */
/*   Updated: 2018/12/03 18:51:47 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "SDL.h"
# include "libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
#include <stdio.h>

# define THREADS 16
# define WIN_W 320
# define WIN_H 200
# define FOV 60
# define BLOCK 64
# define CAM_H BLOCK / 2

# define LEFT_BUTTON 1
# define RIGHT_BUTTON 3
# define ZOOM_IN 4
# define ZOOM_OUT 5
# define ZOOM_LOCK 2

typedef struct		s_cam
{
	double			pos_x;
	double			pos_y;
}					t_cam;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	int				quit;
	double			time;
	double			prev_time;
	double			fps;
	t_cam			*cam;
}					t_env;

typedef struct		s_thrds
{
	t_env			*e;
	int				i;
}					t_thrds;

void				error_wolf(char *err);
int					quit_wolf(t_env *e);
void				init_wolf(t_env *e);

void				create_image(t_env *e);
void				print_image(t_env *e);

int					key_hook(int key, t_env *e);
int					mouse_hook(int btn, int x, int y, t_env *e);
int					mouse_motion(int x, int y, t_env *e);
int					expose_hook(t_env *e);

#endif
