/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_normal_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:41:53 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/04 11:26:39 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

t_p3d	normal_at_sphere(t_sphere *o, t_p3d p)
{
	return (p3d_norm(p3d_sub(p, o->pos)));
}

t_p3d	normal_at_plane(t_plane *o, t_p3d p)
{
	(void)p;
	return (o->norm);
}
