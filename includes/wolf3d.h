/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:37:43 by lfatton           #+#    #+#             */
/*   Updated: 2018/12/27 22:42:44 by lfatton          ###   ########.fr       */
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
# define WIN_W 800
# define WIN_H 600
# define HALF_W WIN_W / 2
# define HALF_H WIN_H / 2
# define FOV 60
# define TILE 64
# define INCR FOV / (double)WIN_W
# define DIST HALF_W / tan(ft_degtorad((double)FOV / 2))
# define RATIO TILE * DIST
# define MAX_DIST (24 + 24) * TILE 

 #define ANGLE60  WIN_W
#define    ANGLE30  (ANGLE60/2)
#define    ANGLE15  (ANGLE30/2)
 #define   ANGLE90  (ANGLE30*3)
#define    ANGLE180  (ANGLE90*2)
#define  ANGLE270  (ANGLE90*3)
#define  ANGLE360  (ANGLE60*6)
#define   ANGLE0  0
#define   ANGLE5  (ANGLE30/6)
#define  ANGLE10  (ANGLE5*2)

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00

# define NORTH 90
# define SOUTH 270
# define WEST 180
# define EAST 0

# define LEFT_BUTTON 1
# define RIGHT_BUTTON 3
# define ZOOM_IN 4
# define ZOOM_OUT 5
# define ZOOM_LOCK 2

typedef struct		s_player
{
	int				height;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				card;
}					t_player;

typedef struct		s_ray
{
	double			step;
	double			angle;

	double			cam_x;
	double			dir_x;
	double			dir_y;
	double			dist_x;
	double			dist_y;
	double			dx;
	double			dy;
	double			length;
	double				step_x;
	double				step_y;
	int				hit;
	double				line_h;

}					t_ray;

typedef struct		s_map
{
	int		*m;
	int				x;
	int				y;
	int				w;
	int				h;
	
}					t_map;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Texture	*text;
	int		*pix;
	int				quit;
	double			time;
	double			prev_time;
	double			fps;
	int				x;
	int				y;
	int				end;
	int				color;
	t_player			*p;
	t_ray				*r;
	t_map				*m;
}					t_env;

typedef struct		s_thrds
{
	t_env			*e;
	int				i;
}					t_thrds;

void				error_wolf(char *err);
int					quit_wolf(t_env *e);
void    raycasting(t_env *e);

void				init_wolf(t_env *e);

void				create_image(t_env *e);
void				print_image(t_env *e);

int					key_hook(int key, t_env *e);
int					mouse_hook(int btn, int x, int y, t_env *e);
int					mouse_motion(int x, int y, t_env *e);
int					expose_hook(t_env *e);

#endif
