/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 20:59:35 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/18 16:08:00 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

#define EPSILON 0.000001f

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

int		intersect_plane(t_plane *o, t_ray ray, float *t)
{
	float denom;

	denom = p3d_dot(o->norm, ray.dir);
	if (fabsf(denom) <= EPSILON)
		return (0);
	*t = p3d_dot(p3d_sub(o->pos, ray.orig), o->norm) / denom;
	if (*t < 0)
		return (0);
	return (1);
}

int		intersect_cone(t_cone *o, t_ray ray, float *t)
{
	double a;
	double b;
	double c;
	double delta;
	double z;

	ray.orig = p3d_sub(ray.orig, o->pos);
	a = o->cosa2 * ray.dir.x * ray.dir.x + o->cosa2 * ray.dir.y * ray.dir.y
				- o->sina2 * ray.dir.z * ray.dir.z;
	b = o->cosa2 * ray.dir.x * ray.orig.x + o->cosa2 * ray.dir.y * ray.orig.y
				- o->sina2 * ray.dir.z * ray.orig.z;
	c = o->cosa2 * ray.orig.x * ray.orig.x + o->cosa2 * ray.orig.y * ray.orig.y
				- o->sina2 * ray.orig.z * ray.orig.z;
	delta = b * b - a * c;
	if (delta < EPSILON)
		return (0);
	*t = (-b - sqrt(delta)) / a;
	if (*t < EPSILON)
		return (0);
	z = ray.orig.z + *t * ray.dir.z;
	if (z < -o->h - EPSILON || z > EPSILON)
		return (0);
	return (1);
}

int		intersect_cylinder(t_cylinder *o, t_ray ray, float *t)
{
	float a;
	float b;
	float c;
	float delta;

	ray.orig = p3d_sub(ray.orig, o->pos);
	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	b = ray.dir.x * ray.orig.x + ray.dir.y * ray.orig.y;
	c = ray.orig.x * ray.orig.x + ray.orig.y * ray.orig.y - o->rad * o->rad;
	delta = b * b - a * c;
	if (delta < EPSILON)
		return (0);
	*t = (-b - sqrt(delta)) / a;
	if (*t <= EPSILON)
		return (0);
	return (1);
}

#undef EPSILON
