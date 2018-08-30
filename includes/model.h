/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:43 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/29 17:36:58 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_H
# define MODEL_H

# include "lib3d.h"
# include "vec.h"
# include "SDL.h"
//# include "util.h"

/*
** Things
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
	// TODO: actual props
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

typedef struct		s_model_data
{
	t_vec			objects;
}					t_model_data;

/*
** Public
*/
const t_model_data	*model_get(void);
int					model_init(void);
void				model_free(void);

#endif
