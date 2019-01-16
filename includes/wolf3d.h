/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:37:43 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/14 12:05:51 by lfatton          ###   ########.fr       */
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
#include <stdio.h>

# define MAP_W 100
# define MAP_H 100
# define BMP_PATH "assets/bmp/basic.bmp"
# define WIN_W 1360
# define WIN_H 764
# define HALF_W WIN_W / 2
# define HALF_H WIN_H / 2
# define FOV 60.0
# define TILE 64
# define SPEED 5
# define DECR_ANG FOV / (double)WIN_W
# define RATIO TILE * (HALF_W / tan(ft_degtorad(FOV / 2)))

# define SKYBLUE 0xFF0EC0EE
# define BROWN 0xFF452209

# define NORTH 90
# define SOUTH 270
# define WEST 180
# define EAST 0
# define CIRCLE 360

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

typedef	struct		s_coords_double
{
	double			x;
	double			y;
}					t_coords_double;

typedef struct 		s_coords
{
	int 			x;
	int 			y;
}					t_coords;

typedef struct		s_player
{
	t_coords_double	pos;
	double			vis;
	double			height;
	int				crouch;
	int				fly;
}					t_player;

typedef struct		s_ray
{
	double			ang;
	double			tan;
	double			h_hit_x;
	double			v_hit_y;
	t_coords_double	hit;
	t_coords_double	text;
	t_coords_double	step;
	double			dist;
	double			length;
	int			    offset;
}					t_ray;

typedef struct		s_sprites
{
	SDL_Surface		*all;
	SDL_Surface		*map;
	SDL_Surface		*wallN;
	SDL_Surface		*wallS;
	SDL_Surface		*wallW;
	SDL_Surface		*wallE;
	SDL_Surface     *wall;
}					t_sprites;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	t_sprites		*sprites;
	t_coords	map_pos;
	int				map_w;
	int				map_h;
	enum TTile		**tiles;
	SDL_Texture		*text;
	SDL_Surface		*surf;
	int				quit;
	int				x;
    int				y;
	int				end;
	Uint32				color;
	int				hori;
	t_player			*p;
	t_ray				*r;
}					t_env;

void				error_wolf(char *err);
int					quit_wolf(t_env *e);
void				init_wolf(t_env *e);
void				loop_wolf(t_env *e);

void				raycasting(t_env *e);

Uint32 				get_pixel(SDL_Surface *s, int x, int y);
void				put_pixel(SDL_Surface *s, int x, int y, Uint32 color);
void				draw(t_env *e);
void				print_image(t_env *e);

void				move_left(t_env *e);
void				move_right(t_env *e);
void				move_down(t_env *e);
void				move_up(t_env *e);
void				crouch_and_fly(t_env *e, int k, int type);

t_sprites			*get_sprites(int ac, char **av, t_env *e);
SDL_Surface			*extract_map(SDL_Surface *all);
enum TTile			**transform_pixels_to_tiles(SDL_Surface *map);
void				read_tiles(t_env *e);
void				verify_map(enum TTile **tiles);
int					apply_to_whole_map(enum TTile **tiles, int (*action)(enum TTile*, int, int));
int					isnt_PlayerSpawn(enum TTile *tile, int x, int y);
int					put_wall_if_border(enum TTile *tile, int x, int y);
#endif
