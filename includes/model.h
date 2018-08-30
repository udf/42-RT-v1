/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:43 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/30 11:03:47 by mhoosen          ###   ########.fr       */
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
typedef enum		e_object
{
	SPHERE,
	CONE,
	CYLINDER,
	PLANE
}					t_e_object;

typedef struct		s_sphere
{
	t_e_object		type;
	t_p3d			pos;
	float			radius;
}					t_sphere;

typedef struct		s_cone
{
	t_e_object		type;
	// TODO: actual props
}					t_cone;

typedef struct		s_cylinder
{
	t_e_object		type;
	// TODO: actual props
}					t_cylinder;

typedef struct		s_plane
{
	t_e_object		type;
	// TODO: actual props
}					t_plane;

typedef union		u_object
{
	t_e_object		type;
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

/*
** Private
*/
int					model_scene_load(const char *scene_path, t_model_data *m);
int					model_obj_sphere_load(char *line, t_object *object);
#endif
