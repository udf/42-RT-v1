/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 10:03:11 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/12 00:28:37 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"
#include "view.h"

static int	read_generic(char **data, t_p3d *out)
{
	if (parse_rgb(*data, out))
		return (1);
	*data += 6;
	return (0);
}

static int	read_float(char **data, float *out)
{
	const char *start = *data;

	*data = (char *)ft_atof_seek(*data, out);
	return (start == *data);
}

static int	read_p3d(char **data, t_p3d *out)
{
	if (read_float(data, &out->x) || ft_tokenseek(data) == 0 || **data != ',')
		return (1);
	*data += 1;
	if (read_float(data, &out->y) || ft_tokenseek(data) == 0 || **data != ',')
		return (1);
	*data += 1;
	if (read_float(data, &out->z))
		return (1);
	return (0);
}

#define TYPE_WR_1(var) if(!ft_strncmp_max(param,#var,len,ft_strlen(#var)))
#define TYPE_WR_2(type, var) if(read_##type(&data,&o->var))return 1;continue;
#define TYPE_WRAPPER(type, s_var, var) TYPE_WR_1(s_var) {TYPE_WR_2(type, var)}

#define GEN_GENERIC TYPE_WRAPPER(generic, colour, g.colour)
#define GEN_P3D(name) TYPE_WRAPPER(p3d, name, name)
#define GEN_FLOAT(name) TYPE_WRAPPER(float, name, name)

#define GEN_S1(ln) int load_##ln(char *data, t_object *obj) {
#define GEN_S2(un, ln) int len;char *param;obj->g.type=un;t_##ln *o=&obj->ln;
#define GEN_S3 while (ft_tokenseek(&data)) {
#define GEN_S4 if ((len = ft_strchr_i(data, '=')) < 0) break;
#define GEN_S5(un) param = data; data += len + 1;GEN_##un;
#define GEN_S6(ln) return SDL_SetError("Can't find \"%.*s\" of "#ln,len,param);
#define GEN_S7(ln) } return verify_##ln(o);}
#define GEN_S_P1(ln, un) GEN_S1(ln) GEN_S2(un, ln)
#define GEN_S_P2(ln, un) GEN_S3 GEN_S4 GEN_S5(un) GEN_S6(ln) GEN_S7(ln)
#define GEN_STRUCT(ln, un) GEN_S_P1(ln, un) GEN_S_P2(ln, un)

GEN_STRUCTS;
GEN_STRUCT(camera, CAMERA);

#undef GEN_STRUCT
#undef GEN_S_P2
#undef GEN_S_P1
#undef GEN_S7
#undef GEN_S6
#undef GEN_S5
#undef GEN_S4
#undef GEN_S3
#undef GEN_S2
#undef GEN_S1
#undef GEN_FLOAT
#undef GEN_P3D
#undef GEN_GENERIC
#undef TYPE_WRAPPER
#undef TYPE_WR_2
#undef TYPE_WR_1

#define GEN_STRUCT_STUB(t_name, name) t_name name;
#define GEN_S1(name_str) if (ft_strncmp(line, name_str, len) == 0)
#define GEN_S2(load_func) return load_func(data, o);
#define GEN_STRUCT(ln, un) GEN_S1(#ln) GEN_S2(load_##ln)

static int	parse_line(char *line, t_object *o)
{
	static size_t	cam_i = 0;
	size_t			len;
	char			*data;
	t_view_data		*v;

	len = ft_tokenseek(&line);
	data = line + len;
	ft_tokenseek(&data);
	GEN_STRUCTS;
	if (ft_strncmp(line, "camera", len) == 0)
	{
		if (cam_i >= 10)
			return (SDL_SetError("Too many cameras"));
		if (load_camera(data, o))
			return (1);
		v = view_get();
		v->cams[cam_i++] = o->camera;
		return (0);
	}
	return (SDL_SetError("Unknown object \"%.*s\"", (int)len, line));
}

#undef GEN_STRUCT
#undef GEN_S2
#undef GEN_S1
#undef GEN_STRUCT_STUB

int			model_scene_load(const char *scene_path, t_model_data *m)
{
	int				fd;
	unsigned char	*line;
	ssize_t			l_n;
	int				err;
	t_object		obj;

	if ((fd = open(scene_path, O_RDONLY)) < 0)
		return (SDL_SetError("Could not open scene file"));
	l_n = 0;
	while (get_next_line(fd, (char **)&line) == GNL_SUCCESS && ++l_n)
	{
		err = parse_line(ft_strlower((char*)line), &obj);
		free(line);
		if (err)
			return (SDL_SetError("Error on line %zd: %s", l_n, SDL_GetError()));
		if (obj.g.type != CAMERA)
			vec_append(&m->objects, &obj);
	}
	close(fd);
	if (m->objects.length == 0)
		return (SDL_SetError("Error: Scene is empty"));
	return (0);
}
