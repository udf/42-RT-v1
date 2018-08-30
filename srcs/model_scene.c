/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 10:03:11 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/30 11:29:22 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

int		model_obj_sphere_load(char *line, t_object *object)
{
	object->type = SPHERE;
	if (!ft_tokenseek_next(&line))
		return (1);
	object->sphere.pos.x = (float)ft_atof(line);
	if (!ft_tokenseek_next(&line))
		return (1);
	object->sphere.pos.y = (float)ft_atof(line);
	if (!ft_tokenseek_next(&line))
		return (1);
	object->sphere.pos.z = (float)ft_atof(line);
	if (!ft_tokenseek_next(&line))
		return (1);
	object->sphere.radius = (float)ft_atof(line);
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
		if (m->obj_loaders[line[0]])
			err = (m->obj_loaders[line[0]])((char*)line, &obj);
		else
			err = 1;
		free(line);
		if (err)
			return (SDL_SetError("Failed to read object on line %zd", line_n));
		vec_append(&m->objects, &obj);
		line_n++;
	}
	close(fd);
	if (m->objects.length == 0)
		return (SDL_SetError("Error: Scene is empty"));
	return (0);
}
