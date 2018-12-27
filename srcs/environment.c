/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:52:06 by lfatton           #+#    #+#             */
/*   Updated: 2018/12/28 00:44:05 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int m[24][24] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	error_wolf(char *err)
{
	ft_putendl(err);
	exit(EXIT_FAILURE);
}

int		quit_wolf(t_env *e)
{
	SDL_DestroyRenderer(e->render);
	SDL_DestroyWindow(e->win);
	SDL_Quit();
	free(e->p);
	free(e->r);
	free(e->m);
	free(e);
	exit(EXIT_SUCCESS);
	return (0);
}

void	print_time(t_env *e)
{
	e->prev_time = e->time;
	e->time = clock();
	e->fps = (e->time - e->prev_time) / 1000.0;
printf("%f", 1.0 / e->fps);
}


/*static void		draw_right_h(t_env *e, double x1)
{
	int	x;
	double y2;
	double x2 = x1;
	y2 = e->end;
	double y1 = e->y;
	x = x1;
	while (x <= x2)
	{
		e->pix[x + (int)(y1 + ((y2 - y1) * (x - x1)) / (x2 - x1)) * WIN_W] = e->color;
		x++;
	}
}

wr6snd5arzJfstatic void		draw_left_h(t_env *e, double x1)
{
	int	x;
	double y2;
	double x2 = x1;
	y2 = e->end;
	double y1 = e->y;
	x = x2;
	while (x <= x1)
	{
		e->pix[x + (int)(y2 + ((y1 - y2) * (x - x2)) / (x1 - x2)) * WIN_W] = e->color;
		x++;
	}
}

static void		draw_up_v(t_env *e, double x1)
{
	int	y;
	double y2;
	double x2 = x1;
	y = e->end;,
	y2 = e->end;
	double y1 = e->y;
	while (y <= y1)
	{
		e->pix[(int)(x2 + ((x1 - x2) * (y - y2)) / (y1 - y2)) + y * WIN_W] = e->color;
		y++;
	}
}

static void		draw_down_v(t_env *e, double x1)
{
	int	y;
	double y2;
	double x2 = x1;
	y = e->y;
	y2 = e->end;
	while (y <=y2)
	{
		e->pix[(int)(x1 + ((x2 - x1) * (y - e->y)) / (y2 - e->y)) + y * WIN_W] = e->color;
		y++;
	}
}

void			draw_line(t_env *e, double x1)
{
	double x2 = x1;
	if (x1 <= x2 && (x2 - x1) >= ft_dabs(e->end - e->y))
			draw_right_h(e, x1);
	if (x2 <= x1 && (x1 - x2) >= ft_dabs(e->y - e->end))
			draw_left_h(e, x1);
	if (e->end <= e->y && (e->y - e->end) >= ft_dabs(x1 - x2))
			draw_up_v(e,  x1);
	if (e->y <= e->end && (e->end - e->y) >= ft_dabs(x1 - x2))
		draw_down_v(e,  x1);
}*/

double	dda(t_env *e)
{
	while ((e->r->dist_x >= 0 && e->r->dist_x < TILE * e->m->w) && (e->r->dist_y >= 0 && e->r->dist_y < TILE * e->m->h))
	{
		e->m->x = (int)(e->r->dist_x / TILE); 
		e->m->y = (int)(e->r->dist_y / TILE);
		if (m[e->m->y][e->m->x] > 0)
		{
	//printf("%d %d\n", e->m->x, e->m->y);
				return (sqrt(ft_sq(e->p->pos_x - e->r->dist_x) + ft_sq(e->p->pos_y - e->r->dist_y)));
		}
		e->r->dist_x += e->r->step_x;
		e->r->dist_y += e->r->step_y;
		
		/*
		while (!e->r->hit)
		{
		if (e->r->dist_x < e->r->dist_y)
       		{
          		e->r->dist_x += e->r->dx;
         		e->m->x += e->r->step_x;
          		e->r->card = 0;
        	}
        	else
        	{
          		e->r->dist_y += e->r->dy;
         		e->m->y += e->r->step_y;
          		e->r->card = 1;
        	}
		if (m[e->m->x][e->m->y] > 0) 
			e->r->hit = 1;
			}*/
	}
	return (MAX_DIST);
	//ft_dabs(e->p->pos_x - e->r->dist_x) / cos(ft_degtorad(e->r->angle));
}

/*void	get_ray_dir(t_env *e)
{
	if (e->r->dir_x < 0)
      	{
        	e->r->step_x = -1;
       		e->r->dist_x = (e->p->pos_x - e->m->x) * e->r->dx;
     	}
	else
      	{
        	e->r->step_x = 1;
       		e->r->dist_x = (e->m->x + 1.0 - e->p->pos_x) * e->r->dx;
      	}
	if (e->r->dir_y < 0)
      	{
        	e->r->step_y = -1;
       		e->r->dist_y = (e->p->pos_y - e->m->y) * e->r->dy;
     	}
     	else
     	{
        	e->r->step_y = 1;
       		e->r->dist_y = (e->m->y + 1.0 - e->p->pos_y) * e->r->dy;
      	}
}*/

/*void	init_raycast(t_env *e)
{
	e->r->cam_pos = 2 * e->x / (double)WIN_W - 1;
	e->r->dir_x = e->p->dir_x + e->p->plane_x * e->r->cam_x;
	e->r->dir_y = e->p->dir_y + e->p->plane_y * e->r->cam_x;
	e->m->x = (int)e->p->pos_x;
	e->m->y = (int)e->p->pos_y;
	e->r->dx = ft_dabs(1 / e->r->dir_x);
	e->r->dy = ft_dabs(1 / e->r->dir_y);
	e->r->hit = 0;
}*/

double	raycast_ver(t_env *e)
{
	e->r->hit = 0;
	if (e->r->angle == SOUTH || e->r->angle == NORTH)
		return (MAX_DIST);
	if (e->r->angle > NORTH && e->r->angle < SOUTH)
	{
		e->r->step_x = -TILE;
		e->r->dist_x = (int)(e->p->pos_x / TILE) * TILE - TILE;
		e->r->dist_y = e->p->pos_y + (e->p->pos_x - e->r->dist_x) * tan(ft_degtorad(e->r->angle));
	}
	else if (e->r->angle < NORTH || e->r->angle > SOUTH)
	{
		e->r->step_x = TILE;
		e->r->dist_x = (int)(e->p->pos_x / TILE) * TILE + TILE;
		if (e->r->angle > SOUTH)
			e->r->dist_y = e->p->pos_y + (e->r->dist_x - e->p->pos_x) * tan(ft_degtorad(360 - e->r->angle));
		else
			e->r->dist_y = e->p->pos_y - (e->r->dist_x - e->p->pos_x) * tan(ft_degtorad(e->r->angle));
	}
	if (e->r->angle == EAST || e->r->angle == WEST)
		e->r->step_y = 0;
	else if (e->r->angle > WEST)
		e->r->step_y = e->r->step_x * tan(ft_degtorad(360 - e->r->angle));
	else
		e->r->step_y = e->r->step_x * tan(ft_degtorad(e->r->angle));
	while (!e->r->hit)
	{
		e->m->x = floor(e->r->dist_x / TILE);
		e->m->y = floor(e->r->dist_y / TILE);
		if (e->m->x > e->m->w || e->m->y > e->m->h || e->r->dist_x < 0 || e->r->dist_y < 0)
			return (MAX_DIST);
		if (m[e->m->y][e->m->x] > 0) 
			e->r->hit = 1;
		e->r->dist_x += e->r->step_x;
		e->r->dist_y += e->r->step_y;
	}
	if (e->r->angle < 346.3 && e->r->angle > 344.8)
printf("HOR step_x %f step_y %f dist_x %f dist_y %f e->m->x %d e->m->y %d\n", e->r->step_x, e->r->step_y, e->r->dist_x, e->r->dist_y, e->m->x, e->m->y);
//	if (e->r->angle < 71.3 && e->r->angle > 41.8)
//printf("VER step_x %f step_y %f dist_x %f dist_y %f e->m->x %d e->m->y %d ANG %f\n\n", e->r->step_x, e->r->step_y, e->r->dist_x, e->r->dist_y, e->m->x, e->m->y, 360-e->r->angle);
	return (sqrt(ft_sq(ft_dabs(e->p->pos_x - e->r->dist_x)) + ft_sq(ft_dabs(e->p->pos_y - e->r->dist_y))));
	if (e->r->angle > WEST)
		return (ft_dabs(e->p->pos_y - e->r->dist_y) / sin(ft_degtorad(360 - e->r->angle)));
	return (ft_dabs(e->p->pos_y - e->r->dist_y) / sin(ft_degtorad(e->r->angle)));
	/*double dist_y;
	if (e->r->angle < 28.0 || e->r->angle <= 18.5)
printf("step_x %f step_y %f dist_x %f dist_y %f e->m->x %d e->m->y %d\n", e->r->step_x, e->r->step_y, e->r->dist_x, e->r->dist_y, e->m->x, e->m->y);
	if (e->r->angle < NORTH || e->r->angle > SOUTH)
	{
		e->r->step_x = TILE;
		e->r->dist_x = (int)(e->p->pos_x / TILE) * TILE + TILE;
	e->r->step_y = e->r->step_x * tan(ft_degtorad(e->r->angle));
	dist_y = e->p->pos_y + (e->p->pos_x - e->r->dist_x) * tan(ft_degtorad(e->r->angle));
	}
	else
	{
		e->r->step_x = -TILE;
		e->r->dist_x = (int)(e->p->pos_x / TILE) * TILE - 1;
	e->r->step_y = e->r->step_x * tan(ft_degtorad(e->r->angle));
	dist_y = e->p->pos_y + (e->p->pos_x - e->r->dist_x) * tan(ft_degtorad(e->r->angle));
	}*/
//printf("angle yy%f step_x %d step_y %d dist_x %d dist_y %d \n",e->r->angle, e->r->step_x, e->r->step_y, e->r->dist_x, e->r->dist_y);
	//return (dda(e));
	/*while ((e->r->dist_x >= 0 && e->r->dist_x < TILE * e->m->w)
			&& (dist_y >= 0 && dist_y < TILE * e->m->h))
	{
		if (m[(int)(dist_y / TILE)][(int)(e->r->dist_x / TILE)] != 0)
			return (ft_dabs(e->p->pos_y - e->r->dist_y) * sin(ft_degtorad(e->r->angle)));
		e->r->dist_x += e->r->step_x;
		e->r->dist_y += e->r->step_y;
	}
return (MAX_DIST);*/
}

double	raycast_hor(t_env *e)
{
	e->r->hit = 0;
	if (e->r->angle == EAST || e->r->angle == WEST)
		return (MAX_DIST);
	if (e->r->angle > EAST && e->r->angle < WEST)
	{
		e->r->step_y = -TILE;
		e->r->dist_y = (int)(e->p->pos_y / TILE) * TILE - TILE;
		e->r->dist_x = e->p->pos_x + (e->p->pos_y - e->r->dist_y) * tan(ft_degtorad(90 - e->r->angle));
	}
	else if (e->r->angle > WEST && e->r->angle < EAST + 360)
	{
		e->r->step_y = TILE;
		e->r->dist_y = (int)(e->p->pos_y / TILE) * TILE + TILE;
		e->r->dist_x = e->p->pos_x + (e->r->dist_y - e->p->pos_y) / tan(ft_degtorad(360 - e->r->angle));
	}
	if (e->r->angle == NORTH || e->r->angle == SOUTH)
		e->r->step_x = 0;
	else if (e->r->angle > WEST)
		e->r->step_x = e->r->step_y / tan(ft_degtorad(360 - e->r->angle));
	else
		e->r->step_x = e->r->step_y / tan(ft_degtorad(e->r->angle));
	while (!e->r->hit)
	{
		e->m->x = floor(e->r->dist_x / TILE);
		e->m->y = floor(e->r->dist_y / TILE);
		if (e->m->x > e->m->w || e->m->y > e->m->h || e->r->dist_x < 0 || e->r->dist_y < 0)
			return (MAX_DIST);
		if (m[e->m->y][e->m->x] > 0) 
			e->r->hit = 1;
		e->r->dist_x += e->r->step_x;
		e->r->dist_y += e->r->step_y;
	}
	if (e->r->angle > WEST)
		return (ft_dabs(e->p->pos_x - e->r->dist_x) / cos(ft_degtorad(360 - e->r->angle)));
	return (ft_dabs(e->p->pos_x - e->r->dist_x) / cos(ft_degtorad(e->r->angle)));
	/*double dist_x;111
	if (e->r->angle > EAST && e->r->angle < WEST)
	{
		e->r->step_y = -TILE;
		e->r->dist_y = (int)(e->p->pos_y / TILE) * TILE - 1;
		e->r->step_x = e->r->step_y / tan(ft_degtorad(e->r->angle));
		dist_x = e->p->pos_x + (e->p->pos_y - e->r->dist_y) / tan(ft_degtorad(e->r->angle));
	}
	else
	{
		e->r->step_y = TILE;
		e->r->dist_y = (int)(e->p->pos_y / TILE) * TILE + TILE;
	e->r->step_x = e->r->step_y / tan(ft_degtorad(e->r->angle));
	dist_x = e->p->pos_x + (e->p->pos_y - e->r->dist_y) / tan(ft_degtorad(e->r->angle));
	}*/
printf("angle %f step_x %f step_y %f dist_x %f dist_y %f \n",e->r->angle, e->r->step_x, e->r->step_y, e->r->dist_x, e->r->dist_y);
	//return (dda(e));
	/*while ((dist_x >= 0 && dist_x < TILE * e->m->w)
			&& (e->r->dist_y >= 0 && e->r->dist_y < TILE * e->m->h))
	{
		if (m[(int)(e->r->dist_y / TILE)][(int)(dist_x / TILE)] != 0)
			return (ft_dabs(e->p->pos_x - dist_x) * cos(ft_degtorad(e->r->angle)));
		dist_x += e->r->step_x;
		e->r->dist_y += e->r->step_y;
	}
	return (MAX_DIST);*/
}

void draw_floor(t_env *e)
{
	e->y = HALF_H;
	e->end = WIN_H - 1;
	while (e->y < e->end)
		e->pix[e->x + e->y++ * WIN_W] = 0x0;
}
void draw_ceil(t_env *e)
{
	e->y = 0;
	e->end = HALF_H;
	while (e->y < e->end)
		e->pix[e->x + e->y++ * WIN_W] = 0xFFFFFF;
}

void draw_line(t_env *e, int x)
{
		while (e->y < e->end)
			e->pix[x + e->y++ * WIN_W] = e->color;

}

void	raycasting(t_env *e)
{
	double	res_h;
	double	res_v;
	int x = 0;
	int y;

	while (x < WIN_W)
	{
		e->r->angle = e->p->card + FOV / 2 - (INCR * x);
		e->r->angle += (e->r->angle < 0) ? 360 : 0;
		e->r->angle -= (e->r->angle >= 360) ? 360 : 0;
		res_h = raycast_hor(e);
		res_v = raycast_ver(e);
		printf("x %d angle %f resh %f ", x, e->r->angle,  res_h);
		printf(" resv %f ", res_v);
		if (res_h < res_v || res_v == 0)
		{
			e->color = GREEN;
			e->r->length = res_h;
		}
		else
		{
			e->color = RED;
			e->r->length = res_v;// * cos(ft_degtorad(e->r->angle));
		}
		draw_ceil(e);
		draw_floor(e);
      		e->r->line_h = TILE / e->r->length * DIST;
		printf("d %f l %f col %d\n",e->r->length,  e->r->line_h, e->color);
      		y = HALF_H - e->r->line_h / 2;
      		e->end = e->r->line_h + y;
//	printf("start %d ",y);
		if (y < 0)
      			y = 0;
      		if (e->end >= WIN_H)
      			e->end = WIN_H - 1;
      		while (y < e->end)
		{
			e->pix[x + y * WIN_W] = e->color;
			y++;
		}
//	printf("end %d\n",e->end);
		x++;
//double fov = (FOV) ;
//double ray_step = fov / (double) WIN_W;
	//	e->r->angle = e->p->card - ANGLE30;
	//	e->r->angle += (e->r->angle < 0) ? ANGLE360 : 0;
	/*while (++e->x < WIN_W)
	{
		e->r->angle = e->p->card + FOV / 2 - (INCR * e->x);
		//e->r->angle = e->p->card - FOV / 2 + (INCR * e->x);
		e->r->angle += (e->r->angle < 0) ? 360 : 0;
		e->r->angle -= (e->r->angle >= 360) ? 360 : 0;
//	printf("angle %f %d\n", e->r->angle, e->x);	
		res_h = raycast_hor(e);
		res_v = raycast_ver(e);
		if (res_h < res_v)
		{	
			e->color = (e->r->angle <= WEST) ? BLUE : GREEN;
			e->r->length = res_h ;// * cos(ft_degtorad(e->r->angle));
		}
		else
		{
			e->color = (e->r->angle <= NORTH || e->r->angle > SOUTH ) ? RED : YELLOW;
			e->r->length = res_v;// * cos(ft_degtorad(e->r->angle));
		}
		draw_ceil(e);
		draw_floor(e);
      		e->r->line_h = TILE / e->r->length * DIST;
//printf("line_h %f length %f res_h %f res_v %f\n",e->r->line_h, e->r->length, res_h, res_v);
      		e->y = HALF_H - e->r->line_h / 2;
      		e->end = HALF_H + e->r->line_h / 2;
		if (e->y < 0)
      			e->y = 0;
      		if (e->end >= WIN_H)
      			e->end = WIN_H - 1;*/
		/*if (e->r->length < MAX_DIST)
		{
			//int b = e->x + ANGLE30;
			int b = e->x * INCR + FOV / 2;
			double t_dis = e->r->length * cos(ft_degtorad(b));
			e->r->line_h = TILE / t_dis * DIST;
      		e->y = HALF_H - e->r->line_h / 2;
      		e->end = e->r->line_h + e->y;
		if (e->y < 0)
      			e->y = 0;
      		if (e->end >= WIN_H)
      			e->end = WIN_H - 1;*/
		//draw_line(e, e->x);
		//}	
		//e->r->angle++;
		//e->r->angle -= (e->r->angle >= ANGLE360) ? ANGLE360 : 0;
		/*init_raycast(e);
		get_ray_dir(e);
		dda(e);
		if (!e->r->card) 
			e->r->length = (e->m->x - e->p->pos_x + (1 - e->r->step_x) / 2) / e->r->dir_x;
      		else      
			e->r->length = (e->m->y - e->p->pos_y + (1 - e->r->step_y) / 2) / e->r->dir_y;
      		e->r->line_h = (int)(WIN_H / e->r->length);
      		e->y = -e->r->line_h / 2 + WIN_H / 2;
      		e->end = e->r->line_h / 2 + WIN_H / 2;
      		if (e->y < 0)
      			e->y = 0;
      		if (e->end >= WIN_H)
      			e->end = WIN_H - 1;
      		while (e->y < e->end)
			e->pix[e->x + e->y++ * WIN_W] = 0xFFFFFF;*/
	}
}

void	init_player(t_env *e)
{
	//e->p->height = TILE / 2;
	e->p->pos_x = 9 * TILE;
	e->p->pos_y = 16 * TILE;
	e->p->card = 0;

	/*e->p->pos_x = 13;
	e->p->pos_y = 8;
	e->p->dir_x = 1;
	e->p->dir_y = 0;
	e->p->plane_x = 0;
	e->p->plane_y = 2. / 3.;*/
}

void	init_wolf(t_env *e)
{
e->m->w = 24;
e->m->h = 24;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error_wolf("error: cannot run SDL");
	if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0, &e->win, &e->render))
		error_wolf("error: cannot create window");
	if (!(e->pix = (int*)malloc(sizeof(int) * WIN_W * WIN_H)))
		error_wolf("error: cannot allocate memory for the image");
	if (!(e->m->m = (int*)malloc(sizeof(int) * e->m->h * e->m->w)))
		error_wolf("error: cannot allocate memory for the map");
	e->quit = 0;
	e->time = 0;
	e->x = -1;
	init_player(e);
}
