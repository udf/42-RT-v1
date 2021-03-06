/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:34 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/12 10:25:13 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

t_view_data			*view_get(void)
{
	static t_view_data view_data;

	return (&view_data);
}

int					view_init(int w, int h, float fov)
{
	static t_generic	empty_t_generic;
	t_view_data			*v;

	v = view_get();
	v->w = w;
	v->h = h;
	v->fov = fov;
	v->win = SDL_CreateWindow("RTv1",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
	if (!v->win)
		return (1);
	v->ren = SDL_CreateRenderer(v->win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!v->ren)
		return (1);
	v->buf.tex = SDL_CreateTexture(v->ren, SDL_PIXELFORMAT_ARGB32,
		SDL_TEXTUREACCESS_STREAMING, w, h);
	if (!v->buf.tex)
		return (1);
	v->cam = &v->cams[0];
	if (v->cam->distance == 0)
		*v->cam = (t_camera){empty_t_generic, {0, 0, 0}, {45, 0, 0}, 5};
	return (0);
}

void				view_free(void)
{
	t_view_data *v;

	v = view_get();
	SDL_DestroyTexture(v->buf.tex);
	SDL_DestroyRenderer(v->ren);
	SDL_DestroyWindow(v->win);
}

void				view_update(void)
{
	const t_model_data	*m = model_get();
	t_view_data			*v;

	v = view_get();
	SDL_LockTexture(v->buf.tex, NULL, (void **)&v->buf.pixels, &v->buf.pitch);
	SDL_RenderClear(v->ren);
	view_render(v, m);
	SDL_UnlockTexture(v->buf.tex);
	SDL_RenderCopy(v->ren, v->buf.tex, NULL, NULL);
	SDL_RenderPresent(v->ren);
}
