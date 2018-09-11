/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:47 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/11 23:08:49 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
# define VIEW_H

# include "libft.h"
# include "lib3d.h"
# include "SDL.h"
# include "util.h"
# include "model.h"

typedef struct		s_buf
{
	SDL_Texture		*tex;
	Uint32			*pixels;
	int				pitch;
}					t_buf;

typedef struct		s_view_data
{
	t_buf			buf;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	float			fov;
	int				w;
	int				h;
	t_p3d			m_rot;
	t_camera		*cam;
	t_camera		cams[10];
}					t_view_data;

/*
** Public
*/
t_view_data			*view_get(void);
int					view_init(int w, int h, float fov);
void				view_free(void);
void				view_update(void);

/*
** Private
*/
void				view_render(t_view_data *v, const t_model_data *m);

/*
** Utility
*/
int					iroundf(float v);
Uint32				*buf_pixel(t_buf *buf, int x, int y);
Uint32				p3d_to_colour(t_p3d p);
int					verify_camera(t_camera *o);


#endif
