/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 12:34:35 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/30 13:43:01 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static int	parse_hex_byte(char *str, Uint8 *out)
{
	char c;

	c = (char)ft_tolower((char)*str);
	str++;
	if (ft_isdigit(c))
		*out = (Uint8)(c - '0');
	else if (c >= 'a' && c <= 'f')
		*out = (Uint8)(c - 'a' + 10);
	else
		return (1);
	*out = (Uint8)(*out << 4);
	c = (char)ft_tolower((char)*str);
	str++;
	if (ft_isdigit(c))
		*out += (Uint8)(c - '0');
	else if (c >= 'a' && c <= 'f')
		*out += (Uint8)(c - 'a' + 10);
	else
		return (1);
	return (0);
}

int			parse_RGB(char *str, t_pixel *colour)
{
	*colour = (t_pixel){0xFF, 0, 0, 0};
	if (parse_hex_byte(str, &colour->r))
		return (1);
	str += 2;
	if (parse_hex_byte(str, &colour->g))
		return (1);
	str += 2;
	if (parse_hex_byte(str, &colour->b))
		return (1);
	return (0);
}
