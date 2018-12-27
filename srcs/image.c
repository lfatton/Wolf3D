/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:53:56 by lfatton           #+#    #+#             */
/*   Updated: 2018/12/14 16:47:29 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			create_image(t_env *e)
{
	e->text = SDL_CreateTexture(e->render,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               WIN_W, WIN_H);
	SDL_UpdateTexture(e->text, NULL, e->pix, WIN_W * sizeof (int));

	SDL_RenderClear(e->render);
	SDL_RenderCopy(e->render, e->text, NULL, NULL);
	SDL_RenderPresent(e->render);
}
