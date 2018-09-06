/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 10:03:11 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/06 14:55:56 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"
#include "view.h"

#define READ_F_REAL1(line, var) if (!ft_tokenseek_next(&line)) return (1);
#define READ_F_REAL2(line, var) var = (float)ft_atof(line);
#define READ_FLOAT(line, var) READ_F_REAL1(line, var) READ_F_REAL2(line, var)

int		model_obj_sphere_load(char *line, t_object *object)
{
	object->g.type = SPHERE;
	object->g.intersect = (t_inter_test)intersect_sphere;
	object->g.normal_at = (t_normal_at)normal_at_sphere;
	if (!ft_tokenseek_next(&line) || parse_rgb(line, &object->g.colour))
		return (1);
	READ_FLOAT(line, object->sphere.pos.x);
	READ_FLOAT(line, object->sphere.pos.y);
	READ_FLOAT(line, object->sphere.pos.z);
	READ_FLOAT(line, object->sphere.radius);
	return (0);
}

int		model_obj_light_load(char *line, t_object *object)
{
	float tmp;

	object->g.type = LIGHT;
	object->g.intersect = (t_inter_test)intersect_light;
	if (!ft_tokenseek_next(&line) || parse_rgb(line, &object->g.colour))
		return (1);
	READ_FLOAT(line, object->light.pos.x);
	READ_FLOAT(line, object->light.pos.y);
	READ_FLOAT(line, object->light.pos.z);
	READ_FLOAT(line, tmp);
	if (tmp <= 0)
		return (1);
	object->g.colour = p3d_mult(object->g.colour, tmp);
	return (0);
}

int		model_obj_plane_load(char *line, t_object *object)
{
	object->g.type = PLANE;
	object->g.intersect = (t_inter_test)intersect_plane;
	object->g.normal_at = (t_normal_at)normal_at_plane;
	if (!ft_tokenseek_next(&line) || parse_rgb(line, &object->g.colour))
		return (1);
	READ_FLOAT(line, object->plane.pos.x);
	READ_FLOAT(line, object->plane.pos.y);
	READ_FLOAT(line, object->plane.pos.z);
	READ_FLOAT(line, object->plane.norm.x);
	READ_FLOAT(line, object->plane.norm.y);
	READ_FLOAT(line, object->plane.norm.z);
	object->plane.norm = p3d_norm(object->plane.norm);
	return (0);
}

int		model_cam_load(char *line, t_object *object)
{
	static size_t	i = 0;
	t_view_data		*v;

	if (i >= 10)
		return (0);
	v = view_get();
	object->g.type = DUMMY;
	READ_FLOAT(line, v->cams[i].pivot.x);
	READ_FLOAT(line, v->cams[i].pivot.y);
	READ_FLOAT(line, v->cams[i].pivot.z);
	READ_FLOAT(line, v->cams[i].rot.x);
	READ_FLOAT(line, v->cams[i].rot.y);
	READ_FLOAT(line, v->cams[i].rot.z);
	READ_FLOAT(line, v->cams[i].distance);
	if (v->cams[i].distance < 1.0f)
		return (1);
	i++;
	return (0);
}

int		model_scene_load(const char *scene_path, t_model_data *m)
{
	int				fd;
	unsigned char	*line;
	ssize_t			line_n;
	int				err;
	t_object		obj;

	if ((fd = open(scene_path, O_RDONLY)) < 0)
		return (SDL_SetError("Could not open scene file"));
	line_n = 0;
	while (get_next_line(fd, (char **)&line) == GNL_SUCCESS)
	{
		err = 1;
		if (m->obj_loaders[line[0]])
			err = (m->obj_loaders[line[0]])((char*)line, &obj);
		free(line);
		if (err)
			return (SDL_SetError("Failed to read object on line %zd", line_n));
		if (obj.g.type != DUMMY)
			vec_append(&m->objects, &obj);
		line_n++;
	}
	close(fd);
	if (m->objects.length == 0)
		return (SDL_SetError("Error: Scene is empty"));
	return (0);
}
