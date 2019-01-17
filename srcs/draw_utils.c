/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:51:58 by lfatton           #+#    #+#             */
/*   Updated: 2019/01/17 19:43:56 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

Uint32	get_pixel(SDL_Surface *s, int x, int y)
{
	Uint32	*pix;

	pix = (Uint32*)s->pixels;
	return (pix[x + y * s->w]);
}

void	put_pixel(SDL_Surface *s, int x, int y, Uint32 color)
{
	Uint32	*pix;

	pix = (Uint32*)s->pixels;
	pix[x + y * s->w] = color;
}

void	print_image(t_env *e)
{
	SDL_DestroyTexture(e->text);
	SDL_RenderClear(e->render);
	if (!(e->text = SDL_CreateTextureFromSurface(e->render, e->surf)))
		error_wolf("error: cannot create texture");
	SDL_RenderCopy(e->render, e->text, NULL, NULL);
	SDL_RenderPresent(e->render);
}
