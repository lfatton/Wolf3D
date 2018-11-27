/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:37:43 by lfatton           #+#    #+#             */
/*   Updated: 2018/11/26 18:18:26 by lfatton          ###   ########.fr       */
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

# define THREADS 16
# define WIN_W 800
# define WIN_H 600
# define BPP 32

# define LEFT_BUTTON 1
# define RIGHT_BUTTON 3
# define ZOOM_IN 4
# define ZOOM_OUT 5
# define ZOOM_LOCK 2

# if __APPLE__
#  include "macos_keys.h"
# else
#  include "linux_keys.h"
# endif

typedef struct	s_img
{
	void		*ptr;
	int			*str;
	double		zoom;
}				t_img;

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_env
{
	SDL_Window	*win;
	SDL_Renderer	*render;
	int			help;
	t_img		*img;
	t_point		*p;
}				t_env;

typedef struct	s_thrds
{
	t_env		*e;
	int			i;
}				t_thrds;

void			parse(t_env *e, int fd);

void			error_wolf(char *err);
int				quit_wolf(t_env *e);
void			init_wolf(t_env *e);

void			create_image(t_env *e);
void			print_image(t_env *e);

int				key_hook(int key, t_env *e);
int				mouse_hook(int btn, int x, int y, t_env *e);
int				mouse_motion(int x, int y, t_env *e);
int				expose_hook(t_env *e);

#endif
