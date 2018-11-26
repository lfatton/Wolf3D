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

# include "mlx.h"
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
# define WIN_W 1920
# define WIN_H 1080


# define LEFT_BUTTON 1
# define RIGHT_BUTTON 3
# define ZOOM_IN 4
# define ZOOM_OUT 5
# define ZOOM_LOCK 2

# if __APPLE__
#  define ESC 53
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_5 23
#  define KEY_6 22
#  define KEY_7 26
#  define KEY_8 28
#  define UP_ARROW 126
#  define DOWN_ARROW 125
#  define LEFT_ARROW 123
#  define RIGHT_ARROW 124
#  define PAD_ADD 69
#  define PAD_SUB 78
#  define PAD_0 82
#  define PAD_1 83
#  define PAD_2 84
#  define PAD_3 85
#  define PAD_4 86
#  define PAD_5 87
#  define PAD_6 88
#  define PAD_7 89
#  define PAD_8 91
#  define PAD_9 92
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_R 15
#  define KEY_C 8
#  define KEY_H 4
#  define KEY_SPACE 49
# else
#  define ESC 65307
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 51
#  define KEY_4 52
#  define KEY_5 53
#  define KEY_6 54
#  define KEY_7 55
#  define KEY_8 56
#  define UP_ARROW 65362
#  define DOWN_ARROW 65364
#  define LEFT_ARROW 65361
#  define RIGHT_ARROW 65363
#  define PAD_ADD 65451
#  define PAD_SUB 65453
#  define PAD_0 65438
#  define PAD_1 65436
#  define PAD_2 65433
#  define PAD_3 65435
#  define PAD_4 65430
#  define PAD_5 65437
#  define PAD_6 65432
#  define PAD_7 65429
#  define PAD_8 65431
#  define PAD_9 65434
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_R 114
#  define KEY_C 99
#  define KEY_H 104
#  define KEY_SPACE 32
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
	void		*mlx_ptr;
	void		*win_ptr;
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
