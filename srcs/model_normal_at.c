/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_normal_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:41:53 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/18 11:26:16 by mhoosen          ###   ########.fr       */
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
	(void)o;
	(void)p;
	// TODO: implement this
	return (t_p3d){0, 0, 0};
}

t_p3d	normal_at_cylinder(t_cylinder *o, t_p3d p)
{
	return (p3d_norm(p3d_sub(p, (t_p3d){o->pos.x, o->pos.y, p.z})));
}
