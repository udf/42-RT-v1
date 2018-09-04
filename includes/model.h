/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:43 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/04 13:34:25 by mhoosen          ###   ########.fr       */
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
union u_object;
typedef int			(*t_inter_test)(union u_object *o, t_ray ray, float *t);
typedef t_p3d		(*t_normal_at)(union u_object *o, t_p3d p);

typedef enum		e_object
{
	SPHERE,
	CONE,
	CYLINDER,
	PLANE,
	LIGHT
}					t_e_object;

typedef struct		s_generic
{
	t_e_object		type;
	t_p3d			colour;
	t_inter_test	intersect;
	t_normal_at		normal_at;
}					t_generic;

typedef struct		s_sphere
{
	t_generic		g;
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
	t_p3d			norm;
	t_p3d			pos;
}					t_plane;

typedef struct		s_light
{
	t_generic		g;
	t_p3d			pos;
}					t_light;

typedef union		u_object
{
	t_generic		g;
	t_sphere		sphere;
	t_cone			cone;
	t_cylinder		cylinder;
	t_plane			plane;
	t_light			light;
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

int					intersect_light(t_light *o, t_ray ray, float *t);
int					intersect_sphere(t_sphere *o, t_ray ray, float *t);
int					intersect_plane(t_plane *o, t_ray ray, float *t);

t_p3d				normal_at_sphere(t_sphere *o, t_p3d p);
t_p3d				normal_at_plane(t_plane *o, t_p3d p);

/*
** Private
*/
int					model_scene_load(const char *scene_path, t_model_data *m);
int					model_obj_sphere_load(char *line, t_object *object);
int					model_obj_light_load(char *line, t_object *object);
int					model_obj_plane_load(char *line, t_object *object);

/*
** Utility
*/
int					parse_rgb(char *str, t_p3d *v_colour);

#endif
