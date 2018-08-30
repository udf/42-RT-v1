/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:42:24 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/30 15:18:21 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

void	mat_set_modelview(t_mat ret, float distance, t_p3d pivot, t_p3d rot)
{
	mat_set_identity(ret);
	mat_translate(ret, -pivot.x, -pivot.y, -pivot.z);
	mat_rotate_z(ret, -rot.z);
	mat_rotate_y(ret, -rot.y);
	mat_rotate_x(ret, -rot.x);
	mat_translate(ret, 0.0f, 0.0f, -distance);
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

// TODO: maybe need view here
Uint32		cast_ray(t_ray ray, const t_vec *objects)
{
	t_pixel ret;

	(void)objects; // TODO: intersection stuff
	ret.a = 0xFF;
	ret.r = (Uint8)((ray.dir.x + 1) / 0.5f * 255.0f);
	ret.g = (Uint8)((ray.dir.y + 1) / 0.5f * 255.0f);
	ret.b = (Uint8)((ray.dir.z + 1) / 0.5f * 255.0f);
	return *((Uint32 *)&ret);
}

void		view_render(t_view_data *v, const t_model_data *m)
{
	t_ip2d	iter;
	t_ray	ray;
	t_mat	world_to_cam;
	t_mat	cam_to_world;
	const float scale = tan_deg(v->fov * 0.5);
	const float image_aspect_ratio = v->w / (float)v->h;

	mat_set_modelview(world_to_cam, v->distance, v->pivot,
		p3d_add(v->rot, v->m_rot)); // TODO check if can modify to give same as inverse
	mat_inverse(cam_to_world, world_to_cam);
	view_render_bk(v);
	ray.orig = mat_vec_mult((t_p3d){0, 0, 0}, cam_to_world);
	printf("ray origin is: %f,%f,%f\n", ray.orig.x, ray.orig.y, ray.orig.z);
	iter.x = -1;
	while (++iter.x < v->w)
	{
		iter.y = -1;
		while (++iter.y < v->h)
		{
			ray.dir.x = (2 * (iter.x + 0.5) / (float)v->w - 1) * image_aspect_ratio * scale;
			ray.dir.y = (1 - 2 * (iter.y + 0.5) / (float)v->h) * scale;
			ray.dir.z = -1;
			ray.dir = p3d_transform(ray.dir, cam_to_world);
			ray.dir = p3d_norm(ray.dir);
			*buf_pixel(&v->buf, iter.x, iter.y) = cast_ray(ray, &m->objects);
		}
	}
	//exit(0);
}
