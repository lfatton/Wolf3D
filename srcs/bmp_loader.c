#include "wolf3d.h"

SDL_Surface		*extract_surface_from_surface(SDL_Surface *src, t_coords start, t_coords dimensions)
{
	SDL_Surface		*new;
	Uint32			*pixels;
	int 			x;
	int				y;

	if (!(new = SDL_CreateRGBSurfaceWithFormat(0, dimensions.x, dimensions.y, 32, src->format->format)))
		return NULL;
	pixels = (Uint32 *)src->pixels;
	y = 0;
	while (y < dimensions.y)
	{
		x = 0;
		while (x < dimensions.x)
		{
			((Uint32 *)new->pixels)[x + (y * dimensions.x)] = pixels[(start.x + x) + ((start.y + y) * src->w)];
			x++;
		}
		y++;
	}
	return (new);
}

void				extract_walls(t_sprites *sprites)
{
	t_coords 		start;
	t_coords		dimensions;

	start.x = 0;
	start.y = MAP_H;
	dimensions.x = TILE;
	dimensions.y = TILE;
	sprites->wallN = extract_surface_from_surface(sprites->all, start, dimensions);
	start.x += TILE;
	sprites->wallS = extract_surface_from_surface(sprites->all, start, dimensions);
	start.x += TILE;
	sprites->wallE = extract_surface_from_surface(sprites->all, start, dimensions);
	start.x += TILE;
	sprites->wallW = extract_surface_from_surface(sprites->all, start, dimensions);
}

t_sprites			*get_sprites(int ac, char **av, t_env *e)
{
	char		*path;
	t_sprites	*sprites;
	t_coords	start;
	t_coords	dimensions;

	start.x = 0;
	start.y = 0;
	dimensions.x = MAP_W;
	dimensions.y = MAP_H;
	if (!(sprites = (t_sprites*)malloc(sizeof(t_sprites))))
		return NULL;
	if (ac)
		path = av[1];
	else
		path = BMP_PATH;
	if (!(sprites->all = SDL_LoadBMP(path)))
		return NULL;
	if (sprites->all->format.BitsPerPixel != 32 || sprites->all->w != MAP_W + TILE)
	    return NULL;
	if (!(sprites->map = extract_surface_from_surface(sprites->all, start, dimensions)))
		return NULL;
	if (!(e->tiles = transform_pixels_to_tiles((sprites->map))))
		return NULL;
	extract_walls(sprites);
	if (!sprites->wallN || !sprites->wallS || !sprites->wallE || !sprites->wallW)
		return NULL;
	verify_map(e->tiles);
//	read_tiles(e);
	return (sprites);
}