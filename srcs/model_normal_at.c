/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_normal_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:41:53 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/18 14:55:25 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

t_p3d	normal_at_sphere(t_sphere *o, t_p3d p)
{
	return (p3d_norm(p3d_sub(p, o->pos)));
}

t_p3d	normal_at_plane(t_plane *o, t_p3d p)
{
	(void)p;
	return (o->norm);
}

t_p3d	normal_at_cone(t_cone *o, t_p3d p)
{
	t_p3d v;
	t_p3d n;

	v = p3d_sub(p, o->pos);
	v = p3d_norm((t_p3d){v.x, v.y, 0});
	n.x = v.x * o->h / o->rad;
	n.y = v.y * o->h / o->rad;
	n.z = o->rad / o->h;
	return (n);
}

t_p3d	normal_at_cylinder(t_cylinder *o, t_p3d p)
{
	return (p3d_norm(p3d_sub(p, (t_p3d){o->pos.x, o->pos.y, p.z})));
}
