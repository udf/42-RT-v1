/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:30 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/29 17:37:53 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

t_model_data			*model_get_real(void)
{
	static t_model_data model_data;

	return (&model_data);
}

const t_model_data		*model_get(void)
{
	return (model_get_real());
}

int						model_init(void)
{
	t_model_data	*m;

	m = model_get_real();
	vec_init(&m->objects, sizeof(t_object), 0);
	return (0);
}

void					model_free(void)
{
	t_model_data	*m;

	m = model_get_real();
	vec_free(&m->objects);
}
