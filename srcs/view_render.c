/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:42:24 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/03 13:30:31 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

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
	float *t_near, t_object **hit_obj)
{
	size_t		i;
	t_object	*object;
	float		t;

	*t_near = INFINITY;
	i = 0;
	while (i < objects->length)
	{
		object = vec_get((t_vec *)objects, i);
		t = INFINITY;
		if (object->g.intersect(object, ray, &t) && t < *t_near)
		{
			*hit_obj = object;
			*t_near = t;
		}
		i++;
	}
	return (*hit_obj != NULL);
}

Uint32		cast_ray(t_ray ray, const t_vec *objects)
{
	t_pixel		ret;
	float		t;
	t_object	*hit_obj;

	hit_obj = NULL;
	ret = (t_pixel){255, 0, 0, 0};
	if (test_intersection(ray, objects, &t, &hit_obj))
	{
		//TODO:shading
		ret = hit_obj->g.colour;
	}
	return *((Uint32 *)&ret);
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
			ray.dir.y = (1 - 2 * (iter.y + 0.5) / (float)v->h) * scale * 1 / image_aspect_ratio;
			ray.dir.z = -1;
			ray.dir = mat_dir_mult(ray.dir, cam_to_world);
			ray.dir = p3d_norm(ray.dir);
			if (iter.x == 399 && iter.y == 299)
				printf("%d,%d: %.2f,%.2f,%.2f   %.2f,%.2f,%.2f\n",
					iter.x, iter.y,
					ray.orig.x, ray.orig.y, ray.orig.z,
					ray.dir.x, ray.dir.y, ray.dir.z);
			*buf_pixel(&v->buf, iter.x, iter.y) = cast_ray(ray, &m->objects);
		}
	}
}
