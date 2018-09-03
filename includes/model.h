/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:43 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/30 21:52:24 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_H
# define MODEL_H

# include <fcntl.h>

# include "lib3d.h"
# include "get_next_line.h"
# include "vec.h"
# include "SDL.h"
# include "util.h"

/*
** Objects
*/
union				u_object;
typedef int			(*t_inter_test)(union u_object *o, t_ray ray, float *t);

typedef enum		e_object
{
	SPHERE,
	CONE,
	CYLINDER,
	PLANE
}					t_e_object;

typedef struct		s_generic
{
	t_e_object		type;
	t_pixel			colour;
	t_inter_test	intersect;
}					t_generic;

typedef struct		s_sphere
{
	t_generic		g;
	t_pixel			colour;
	t_p3d			pos;
	float			radius;
}					t_sphere;

typedef struct		s_cone
{
	t_generic		g;
	// TODO: actual props
}					t_cone;

typedef struct		s_cylinder
{
	t_generic		g;
	// TODO: actual props
}					t_cylinder;

typedef struct		s_plane
{
	t_generic		g;
	// TODO: actual props
}					t_plane;

typedef union		u_object
{
	t_generic		g;
	t_sphere		sphere;
	t_cone			cone;
	t_cylinder		cylinder;
	t_plane			plane;
}					t_object;

typedef int			(*t_objloader)(char *line, t_object *object);

typedef struct		s_model_data
{
	t_vec			objects;
	t_objloader		obj_loaders[256];
}					t_model_data;

/*
** Public
*/
const t_model_data	*model_get(void);
int					model_init(const char *scene_path);
void				model_free(void);

int					intersect_sphere(t_sphere *o, t_ray ray, float *t);

/*
** Private
*/
int					model_scene_load(const char *scene_path, t_model_data *m);
int					model_obj_sphere_load(char *line, t_object *object);

/*
** Utility
*/
int					parse_RGB(char *str, t_pixel *colour);

#endif
