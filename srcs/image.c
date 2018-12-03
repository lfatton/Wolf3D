/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:53:56 by lfatton           #+#    #+#             */
/*   Updated: 2018/12/03 17:04:14 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			create_image(t_env *e)
{
	SDL_SetRenderDrawColor(e->render, 0, 0, 0, 255);
	SDL_RenderClear(e->render);
	SDL_RenderPresent(e->render);
}
