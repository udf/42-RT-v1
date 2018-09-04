/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 20:59:35 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/04 10:11:39 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

int		intersect_sphere(t_sphere *o, t_ray ray, float *t)
{
	const float	radius2 = o->radius * o->radius;
	float		tca;
	float		d2;
	float		thc;
	t_p3d		l;

	l = p3d_sub(o->pos, ray.orig);
	tca = p3d_dot(l, ray.dir);
	if (tca < 0)
		return (0);
	d2 = p3d_dot(l, l) - tca * tca;
	if (d2 > radius2)
		return (0);
	thc = sqrt(radius2 - d2);
	*t = MIN(-thc, thc) + tca;
	if (*t < 0)
		*t = MAX(-thc, thc) + tca;
	return (*t >= 0);
}

int		intersect_light(t_light *o, t_ray ray, float *t)
{
	(void)o;
	(void)ray;
	(void)t;
	return (0);
}
