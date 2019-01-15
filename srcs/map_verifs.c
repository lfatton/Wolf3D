#include "wolf3d.h"

int					put_wall_if_border(enum TTile *tile, int x, int y)
{
	if (y == 0 || y == MAP_H - 1 || x == 0 || x == MAP_W - 1)
		*tile = tWall;
	return (1);
}

int					isnt_PlayerSpawn(enum TTile *tile, int x, int y)
{
	(void)x;
	(void)y;
	if (*tile == tPlayerSpawn)
		return (0);
	return (1);
}

int					apply_to_whole_map(enum TTile **tiles, int (*action)(enum TTile*, int, int))
{
	int				x;
	int				y;
	int				ret;

	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W) {
			ret = (*action)(&(tiles[y][x]), y, x);
			if (!ret)
				return (ret);
			x++;
		}
		y++;
	}
	return (ret);
}


void			verify_map(enum TTile **tiles)
{
	(void)apply_to_whole_map(tiles, &put_wall_if_border);
	if (apply_to_whole_map(tiles, &isnt_PlayerSpawn))
		tiles[rand() % (MAP_H - 2) + 1][rand() % (MAP_W - 2) + 1] = tPlayerSpawn;
}