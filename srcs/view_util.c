/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:46:18 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/02 23:02:15 by mhoosen          ###   ########.fr       */
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
