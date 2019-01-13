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
# define MAP_W 100
# define MAP_H 100
# define FOV 60
# define BLOCK 64
# define CAM_H BLOCK / 2
# define BMP_PATH "assets/bmp/maptest.bmp"
# define LEFT_BUTTON 1
# define RIGHT_BUTTON 3
# define ZOOM_IN 4
# define ZOOM_OUT 5
# define ZOOM_LOCK 2

enum				TPixColor_ABGR
{
	tRed = 3,
	tGreen = 2,
	tBlue = 1
};

enum				TTile
{
	tWall,
	tPlayerSpawn,
	tEmpty
};

typedef struct		s_cam
{
	double			pos_x;
	double			pos_y;
}					t_cam;

typedef struct		s_sprites
{
	SDL_Surface		*all;
	SDL_Surface		*map;
	SDL_Surface		*north_wall;
	SDL_Surface		*south_wall;
	SDL_Surface		*west_wall;
	SDL_Surface		*east_wall;
}					t_sprites;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	t_sprites		*sprites;
	int				map_w;
	int				map_h;
	enum TTile		**tiles;
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

t_sprites			*get_sprites(int ac, char **av, t_env *e);
SDL_Surface			*extract_map(SDL_Surface *all);
enum TTile			**transform_pixels_to_tiles(SDL_Surface *map);
void				read_tiles(t_env *e);
void				verify_map(enum TTile **tiles);
int					apply_to_whole_map(enum TTile **tiles, int (*action)(enum TTile*, int, int));
int					isnt_PlayerSpawn(enum TTile *tile, int x, int y);
int					put_wall_if_border(enum TTile *tile, int x, int y);

#endif
