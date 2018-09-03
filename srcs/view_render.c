/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:42:24 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/03 19:56:21 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

#define VEC_FOR(vec, ctr) for (size_t ctr = 0; ctr < vec->length; ++ctr)

void   cam_to_w_modelview(t_mat ret, float distance, t_p3d pivot, t_p3d rot)
{
	mat_set_identity(ret);
	mat_translate(ret, 0.0f, 0.0f, distance);
	mat_rotate_x(ret, rot.x);
	mat_rotate_y(ret, rot.y);
	mat_rotate_z(ret, rot.z);
	mat_translate(ret, pivot.x, pivot.y, pivot.z);
}

void		view_render_bk(t_view_data *v)
{
	int x;
	int y;

	y = 0;
	while (y < v->h)
	{
		x = 0;
		while (x < v->w)
		{
			*buf_pixel(&v->buf, x, y) = 0;
			x++;
		}
		y++;
	}
}

int			test_intersection(t_ray ray, const t_vec *objects,
	float *t_near_out, t_object **hit_obj_out)
{
	size_t		i;
	t_object	*object;
	float		t;
	float		t_nearest;
	t_object	*hit_obj;

	i = 0;
	t_nearest = INFINITY;
	hit_obj = NULL;
	while (i < objects->length)
	{
		object = vec_get((t_vec *)objects, i);
		t = INFINITY;
		if (object->g.intersect(object, ray, &t) && t < t_nearest)
		{
			hit_obj = object;
			t_nearest = t;
		}
		i++;
	}
	if (hit_obj_out)
		*hit_obj_out = hit_obj;
	if (t_near_out)
		*t_near_out = t_nearest;
	return (hit_obj != NULL);
}

Uint32		cast_ray(t_ray ray, const t_vec *objects)
{
	t_p3d		out_colour;
	float		t;
	t_object	*hit_obj;
	t_p3d		phit;
	t_p3d		nhit;
	size_t		i;
	t_object	*l_obj;
	t_ray		sh_ray;

	hit_obj = NULL;
	out_colour = (t_p3d){0, 0, 0};
	if (test_intersection(ray, objects, &t, &hit_obj))
	{
		i = 0;
		out_colour = hit_obj->g.colour;
		phit = p3d_add(ray.orig, p3d_mult(ray.dir, t));
		nhit = hit_obj->g.normal_at(hit_obj, phit);
		sh_ray.orig = p3d_add(phit, p3d_mult(nhit, 0.0001));
		while (i < objects->length)
		{
			l_obj = vec_get((t_vec *)objects, i);
			if (l_obj->g.type == LIGHT)
			{
				sh_ray.dir = p3d_norm(p3d_sub(l_obj->light.pos, phit));
				if (!test_intersection(sh_ray, objects, NULL, NULL))
				{
					out_colour = p3d_add(out_colour, p3d_mult(l_obj->g.colour,
						MAX(0.0f, p3d_dot(nhit, sh_ray.dir))));
				}
			}
			i++;
		}
	}
	return (p3d_to_colour(out_colour));
}

void		view_render(t_view_data *v, const t_model_data *m)
{
	t_ip2d	iter;
	t_ray	ray;
	t_mat	cam_to_world;
	const float scale = tan_deg(v->fov * 0.5);
	const float image_aspect_ratio = v->w / (float)v->h;

	cam_to_w_modelview(cam_to_world, v->distance, v->pivot,
		p3d_add(v->rot, v->m_rot));
	view_render_bk(v);
	ray.orig = mat_vec_mult((t_p3d){0, 0, 0}, cam_to_world);
	iter.y = -1;
	while (++iter.y < v->h)
	{
		iter.x = -1;
		while (++iter.x < v->w)
		{
			ray.dir.x = (2 * (iter.x + 0.5) / (float)v->w - 1) * scale;
			ray.dir.y = (1 - 2 * (iter.y + 0.5) / (float)v->h)
						* scale * 1 / image_aspect_ratio;
			ray.dir.z = -1;
			ray.dir = p3d_norm(mat_dir_mult(ray.dir, cam_to_world));
			*buf_pixel(&v->buf, iter.x, iter.y) = cast_ray(ray, &m->objects);
		}
	}
}
