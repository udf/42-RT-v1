/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:42:24 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/29 22:14:48 by mhoosen          ###   ########.fr       */
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

t_p2d	t_p2d_lerp(float frac, t_p2d start, t_p2d end)
{
	return (t_p2d){start.x + (end.x - start.x) * frac,
		start.y + (end.y - start.y) * frac};
}

t_p2d	p2d_roundf(t_p2d p)
{
	return (t_p2d){roundf(p.x), roundf(p.y)};
}

static void	point_clip(t_p2d *p, float w, float h, t_p2d m)
{
	t_p2d	clamped;

	clamped.x = CLAMP(p->x, 0, w - 1.0f);
	if (isfinite(m.y))
		p->y = m.y * (clamped.x - p->x) + p->y;
	p->x = clamped.x;
	clamped.y = CLAMP(p->y, 0, h - 1.0f);
	if (isfinite(m.x))
		p->x = m.x * (clamped.y - p->y) + p->x;
	p->y = clamped.y;
}

int			line_clip(t_p2d *a, t_p2d *b, float w, float h)
{
	const t_p2d m = {(b->x - a->x) / (b->y - a->y),

	(b->y - a->y) / (b->x - a->x)};
	point_clip(a, w, h, m);
	point_clip(b, w, h, m);
	return ((a->x < 0 || a->x >= w || a->y < 0 || a->y >= h)
				&& (b->x < 0 || b->x >= w || b->y < 0 || b->y >= h));
}

void	put_line(t_view_data *v, t_p2d a, t_p2d b, Uint32 colour)
{
	long	i;
	long	steps;
	t_p2d	p;

	if (line_clip(&a, &b, (float)v->w, (float)v->h))
		return ;
	a = (t_p2d){roundf(a.x), roundf(a.y)};
	b = (t_p2d){roundf(b.x), roundf(b.y)};
	steps = (long)MAX(ABS(b.x - a.x), ABS(b.y - a.y));
	i = 0;
	while (i < steps)
	{
		p = p2d_roundf(t_p2d_lerp((float)i / (float)steps, a, b));
		*buf_pixel(&v->buf, (int)roundf(p.x), (int)roundf(p.y)) = colour;
		i++;
	}
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

t_p2d		p3d_truncz(t_p3d p)
{
	return (t_p2d){p.x, p.y};
}

void		aaa(t_view_data *v)
{
	t_mat		world_to_cam;
	const t_p2d	raster_size = {(float)v->w, (float)v->h};
	t_p3d		verts[8] =
	{
		{-1, -1, -1},
		{ 1, -1, -1},
		{-1,  1, -1},
		{ 1,  1, -1},
		{-1, -1, 1},
		{ 1, -1, 1},
		{-1,  1, 1},
		{ 1,  1, 1}
	};

	mat_set_modelview(world_to_cam, v->distance, v->pivot,
		p3d_add(v->rot, v->m_rot));
	for (int i = 0; i < 8; ++i)
	{
		verts[i] = p3d_project(v->distance, raster_size, verts[i], world_to_cam);
	}

	put_line(v, p3d_truncz(verts[0]), p3d_truncz(verts[1]), 0x00FF0000);
	put_line(v, p3d_truncz(verts[1]), p3d_truncz(verts[3]), 0x00FF0000);
	put_line(v, p3d_truncz(verts[3]), p3d_truncz(verts[2]), 0x00FF0000);
	put_line(v, p3d_truncz(verts[2]), p3d_truncz(verts[0]), 0x00FF0000);

	put_line(v, p3d_truncz(verts[4]), p3d_truncz(verts[5]), 0x00FF0000);
	put_line(v, p3d_truncz(verts[5]), p3d_truncz(verts[7]), 0x00FF0000);
	put_line(v, p3d_truncz(verts[7]), p3d_truncz(verts[6]), 0x00FF0000);
	put_line(v, p3d_truncz(verts[6]), p3d_truncz(verts[4]), 0x00FF0000);

	put_line(v, p3d_truncz(verts[0]), p3d_truncz(verts[4]), 0x00FF0000);
	put_line(v, p3d_truncz(verts[1]), p3d_truncz(verts[5]), 0x00FF0000);
	put_line(v, p3d_truncz(verts[2]), p3d_truncz(verts[6]), 0x00FF0000);
	put_line(v, p3d_truncz(verts[3]), p3d_truncz(verts[7]), 0x00FF0000);
}

void		view_render(t_view_data *v, const t_model_data *m)
{
	(void)m; // TODO: use m.objects to render

	view_render_bk(v);

	aaa(v);
}
