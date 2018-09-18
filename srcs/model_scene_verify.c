/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_scene_verify.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 21:20:43 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/18 15:11:48 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

int	verify_sphere(t_sphere *o)
{
	o->g.intersect = (t_inter_test)intersect_sphere;
	o->g.normal_at = (t_normal_at)normal_at_sphere;
	return (0);
}

int	verify_plane(t_plane *o)
{
	o->norm = p3d_norm(o->norm);
	if (p3d_dot(o->norm, o->norm) < 0.9f)
		return (SDL_SetError("Plane has invalid normal"));
	o->g.intersect = (t_inter_test)intersect_plane;
	o->g.normal_at = (t_normal_at)normal_at_plane;
	return (0);
}

int	verify_cone(t_cone *o)
{
	double	d;

	o->g.intersect = (t_inter_test)intersect_cone;
	o->g.normal_at = (t_normal_at)normal_at_cone;
	o->pos.z += o->h;
	d = p3d_mag(p3d_sub(
		(t_p3d){o->pos.x, o->pos.y, o->pos.z + o->h},
		(t_p3d){o->pos.x + o->rad, o->pos.y, o->pos.z}));
	o->cosa2 = o->h / d;
	o->sina2 = o->rad / d;
	return (0);
}

int	verify_light(t_light *o)
{
	if (o->intensity <= 0)
		return (SDL_SetError("Light has an intensity <= 0"));
	o->g.intersect = (t_inter_test)intersect_light;
	o->g.colour = p3d_mult(o->g.colour, o->intensity);
	return (0);
}

int	verify_cylinder(t_cylinder *o)
{
	o->g.intersect = (t_inter_test)intersect_cylinder;
	o->g.normal_at = (t_normal_at)normal_at_cylinder;
	return (0);
}
