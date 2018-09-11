/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 12:34:35 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/10 21:27:51 by mhoosen          ###   ########.fr       */
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

int			parse_rgb(char *str, t_p3d *v_colour)
{
	t_pixel colour;

	colour = (t_pixel){0xFF, 0, 0, 0};
	if (parse_hex_byte(str, &colour.r))
		return (1);
	str += 2;
	if (parse_hex_byte(str, &colour.g))
		return (1);
	str += 2;
	if (parse_hex_byte(str, &colour.b))
		return (1);
	v_colour->x = (float)colour.r / 255.0f;
	v_colour->y = (float)colour.g / 255.0f;
	v_colour->z = (float)colour.b / 255.0f;
	return (0);
}

int			ft_strchr_i(const char *s, char c)
{
	int	i;

	i = 0;
	while (1)
	{
		if (s[i] == (char)c)
			return (i);
		if (!s[i])
			break ;
		i++;
	}
	return (-1);
}

int		ft_strncmp_max(const char *s1, const char *s2, size_t l1, size_t l2)
{
	return (ft_strncmp(s1, s2, MAX(l1, l2)));
}
