#include "wolf3d.h"

t_sprites			*get_sprites(int ac, char **av, t_env *e)
{
	char		*path;
	t_sprites	*sprites;

	if (!(sprites = (t_sprites*)malloc(sizeof(t_sprites))))
		return NULL;
	if (ac)
		path = av[1];
	else
		path = BMP_PATH;
	if (!(sprites->all = SDL_LoadBMP(path)))
		return NULL;
	if (!(sprites->map = extract_map(sprites->all)))
		return NULL;
	if (!(e->tiles = transform_pixels_to_tiles((sprites->map))))
		return NULL;
	verify_map(e->tiles);
	//read_tiles(e);
	return (sprites);
}