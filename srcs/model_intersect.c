/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 20:59:35 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/02 23:56:59 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

int		intersect_sphere(t_sphere *o, t_ray ray, float *t)
{
	const float radius2 = o->radius * o->radius;
	float tca;
	float d2;
	float thc;
	t_p3d L;

	L = p3d_sub(o->pos, ray.orig);
	tca = p3d_dot(L, ray.dir);
	if (tca < 0)
		return 0;
	d2 = p3d_dot(L, L) - tca * tca;
	if (d2 > radius2)
		return 0;
	thc = sqrt(radius2 - d2);
	*t = MIN(-thc, thc) + tca;
	if (*t < 0)
		*t = MAX(-thc, thc) + tca;
	return *t >= 0;
}
