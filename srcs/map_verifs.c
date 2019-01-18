/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verifs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:59:34 by mtorsell          #+#    #+#             */
/*   Updated: 2019/01/17 23:59:38 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int					put_wall_if_border(enum e_tile *tile, int x, int y)
{
	if (y == 0 || y == MAP_H - 1 || x == 0 || x == MAP_W - 1)
		*tile = t_wall;
	return (1);
}

int					is_not_p_spawn(enum e_tile *tile, int x, int y)
{
	(void)x;
	(void)y;
	if (*tile == t_p_spawn)
		return (0);
	return (1);
}

int					apply_to_whole_map(enum e_tile **til,
						int (*action)(enum e_tile*, int, int))
{
	int				x;
	int				y;
	int				ret;

	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W)
		{
			ret = (*action)(&(til[y][x]), y, x);
			if (!ret)
				return (ret);
			x++;
		}
		y++;
	}
	return (ret);
}

void				verify_map(enum e_tile **til)
{
	Uint32		x;
	Uint32		y;

	(void)apply_to_whole_map(til, &put_wall_if_border);
	if (apply_to_whole_map(til, &is_not_p_spawn))
	{
		x = rand() % (MAP_W - 3) + 1;
		y = rand() % (MAP_H - 3) + 1;
		til[y][x] = t_p_spawn;
		til[y + 1][x] = t_nil;
		til[y - 1][x] = t_nil;
		til[y][x + 1] = t_nil;
		til[y][x - 1] = t_nil;
		til[y + 1][x + 1] = t_nil;
		til[y + 1][x - 1] = t_nil;
		til[y - 1][x - 1] = t_nil;
		til[y - 1][x + 1] = t_nil;
	}
}
