/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:46:18 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/04 21:40:49 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

int			iroundf(float v)
{
	return ((int)roundf(v));
}

Uint32		*buf_pixel(t_buf *buf, int x, int y)
{
	const int pitch = buf->pitch / (int)sizeof(Uint32);

	return (&buf->pixels[x + pitch * y]);
}

Uint32		p3d_to_colour(t_p3d p)
{
	t_pixel pix;

	p = p3d_clip(p, 0.0f, 1.0f);
	pix.a = 255;
	pix.r = (Uint8)(p.x * 255.0f);
	pix.g = (Uint8)(p.y * 255.0f);
	pix.b = (Uint8)(p.z * 255.0f);
	return (*((Uint32 *)(&pix)));
}
