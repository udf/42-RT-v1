/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:30 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/06 12:10:27 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

t_model_data		*model_get_real(void)
{
	static t_model_data model_data;

	return (&model_data);
}

const t_model_data	*model_get(void)
{
	return (model_get_real());
}

int					model_init(const char *scene_path)
{
	t_model_data	*m;

	m = model_get_real();
	vec_init(&m->objects, sizeof(t_object), 0);
	m->obj_loaders['S'] = model_obj_sphere_load;
	m->obj_loaders['L'] = model_obj_light_load;
	m->obj_loaders['P'] = model_obj_plane_load;
	m->obj_loaders['@'] = model_cam_load;
	return (model_scene_load(scene_path, m));
}

void				model_free(void)
{
	t_model_data	*m;

	m = model_get_real();
	vec_free(&m->objects);
}
