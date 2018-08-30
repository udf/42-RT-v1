/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 09:49:56 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/30 15:12:09 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

typedef struct	s_ip2d
{
	int x;
	int y;
}				t_ip2d;

typedef struct	s_pixel
{
	Uint8		a;
	Uint8		r;
	Uint8		g;
	Uint8		b;
}				t_pixel;

#endif
