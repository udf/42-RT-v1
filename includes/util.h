/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 09:49:56 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/04 10:06:26 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "lib3d.h"

typedef struct	s_ip2d
{
	int x;
	int y;
}				t_ip2d;

typedef struct	s_pixel
{
	Uint8		a;
	Uint8		r;
	Uint8		g;
	Uint8		b;
}				t_pixel;

typedef struct	s_ray
{
	t_p3d		orig;
	t_p3d		dir;
}				t_ray;

#endif
