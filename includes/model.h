/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:43 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/12 00:14:14 by mhoosen          ###   ########.fr       */
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
union u_tmp;
typedef int			(*t_inter_test)(union u_tmp *o, t_ray ray, float *t);
typedef t_p3d		(*t_normal_at)(union u_tmp *o, t_p3d p);

/*
** Macros for generating structs
*/
# define GEN_SPHERE GEN_GENERIC GEN_P3D(pos) GEN_FLOAT(radius)
# define GEN_PLANE GEN_GENERIC GEN_P3D(norm) GEN_P3D(pos)
# define GEN_CONE GEN_GENERIC //TODO
# define GEN_CYLINDER GEN_GENERIC //TODO
# define GEN_LIGHT GEN_GENERIC GEN_P3D(pos) GEN_FLOAT(intensity)

/*
** Wrapper that makes all structs
*/
# define GEN_STRUCTS1 GEN_STRUCT(sphere, SPHERE) GEN_STRUCT(plane, PLANE)
# define GEN_STRUCTS2 GEN_STRUCT(cone, CONE) GEN_STRUCT(light, LIGHT)
# define GEN_STRUCTS3 GEN_STRUCT(cylinder, CYLINDER)
# define GEN_STRUCTS GEN_STRUCTS1 GEN_STRUCTS2 GEN_STRUCTS3

/*
** Enumeration of all object types
*/
typedef enum		e_object
{
	SPHERE,
	CONE,
	CYLINDER,
	PLANE,
	LIGHT,
	CAMERA
}					t_e_object;

/*
** Every object contains a generic struct in the g attribute
*/
typedef struct		s_generic
{
	t_e_object		type;
	t_p3d			colour;
	t_inter_test	intersect;
	t_normal_at		normal_at;
}					t_generic;

/*
** Temporarily define how to make the structures as well as their components
*/
# define GEN_GENERIC t_generic g;
# define GEN_P3D(name) t_p3d name;
# define GEN_FLOAT(name) float name;
# define GEN_STRUCT(ln, un) typedef struct {GEN_##un} t_##ln;

/*
** Make sure that camera has a generic attribute (so its g.type can be checked)
*/
# define GEN_CAMERA GEN_GENERIC GEN_P3D(pivot) GEN_P3D(rot) GEN_FLOAT(distance)

/*
** Actually make structs
*/
GEN_STRUCTS;
GEN_STRUCT(camera, CAMERA);

/*
** Remove the generic attribute from camera, because we don't need to load a
** colour from the generated structure loading code (see model_scene.c)
*/
# undef GEN_CAMERA
# define GEN_CAMERA GEN_P3D(pivot) GEN_P3D(rot) GEN_FLOAT(distance)

/*
** Undefine the temporary macros
*/
# undef GEN_STRUCT
# undef GEN_FLOAT
# undef GEN_P3D
# undef GEN_GENERIC

# define GEN_STRUCT_STUB(t_name, name) t_name name;
# define GEN_STRUCT(name, uname) GEN_STRUCT_STUB(t_##name, name)
# define CAMERA t_camera camera
# define GEN_U typedef union u_tmp {t_generic g; CAMERA; GEN_STRUCTS} t_object;

GEN_U;

# undef GEN_U
# undef CAMERA
# undef GEN_STRUCT
# undef GEN_STRUCT_STUB

typedef struct		s_model_data
{
	t_vec			objects;
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
int					intersect_cone(t_cone *o, t_ray ray, float *t);
int					intersect_cylinder(t_cylinder *o, t_ray ray, float *t);

t_p3d				normal_at_sphere(t_sphere *o, t_p3d p);
t_p3d				normal_at_plane(t_plane *o, t_p3d p);
t_p3d				normal_at_cone(t_cone *o, t_p3d p);
t_p3d				normal_at_cylinder(t_cylinder *o, t_p3d p);

/*
** Private
*/
int					model_scene_load(const char *scene_path, t_model_data *m);
int					verify_sphere(t_sphere *o);
int					verify_plane(t_plane *o);
int					verify_cone(t_cone *o);
int					verify_light(t_light *o);
int					verify_cylinder(t_cylinder *o);

/*
** Utility
*/
int					parse_rgb(char *str, t_p3d *v_colour);
int					ft_strchr_i(const char *s, char c);
int					ft_strncmp_max(const char *s1, const char *s2,
														size_t l1, size_t l2);


#endif
