
#include "minirt.h"

void	check_sphere(char *buffer, t_system *sys)
{
	int				i;
	t_object		*obj;

	i = 0;
	while (buffer[i])
	{
		if (ft_strncmp(buffer + i, "sp", 2) == 0
			&& (i == 0 || buffer[i - 1] == '\n'))
		{
			i += 2;
			if (sys->object_count >= MAX_OBJECTS)
				error_exit("Too many objects.\n", sys);
		obj = &sys->obj_list[sys->object_count++];
		obj->type = SPHERE;
		obj->flags = OBJ_VISIBLE | OBJ_CASTS_SHADOW;
		phong_to_material(&obj->material);
			i += parse_xyz(buffer + i, &obj->sphere.location, POINT, sys);
			i += parse_float(buffer + i, &obj->sphere.radius, POSITIVE, sys);
			i += parse_rgb(buffer + i, &obj->material.color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
}

static void	max_object_check(t_system *sys)
{
	if (sys->object_count >= MAX_OBJECTS)
		error_exit("Too many objects.\n", sys);
}

void	check_cylinder(char *buffer, t_system *s)
{
	int			i;
	t_object	*obj;

	i = 0;
	while (buffer[i])
	{
		if (ft_strncmp(buffer + i, "cy", 2) == 0
			&& (i == 0 || buffer[i - 1] == '\n'))
		{
			i += 2;
			max_object_check(s);
		obj = &s->obj_list[s->object_count++];
		obj->type = CYLINDER;
		obj->flags = OBJ_VISIBLE | OBJ_CASTS_SHADOW;
		phong_to_material(&obj->material);
			i += parse_xyz(buffer + i, &obj->cylinder.location, POINT, s);
			i += parse_xyz(buffer + i, &obj->cylinder.rotation, VECTOR, s);
			normalize_or_error(&obj->cylinder.rotation, s);
			i += parse_float(buffer + i, &obj->cylinder.diameter, POSITIVE, s);
			i += parse_float(buffer + i, &obj->cylinder.length, POSITIVE, s);
			i += parse_rgb(buffer + i, &obj->material.color, s);
			i += skip_to_end(buffer + i, s);
			continue ;
		}
		i++;
	}
}

void	check_plane(char *buffer, t_system *sys)
{
	int				i;
	t_object		*obj;

	i = 0;
	while (buffer[i])
	{
		if (ft_strncmp(buffer + i, "pl", 2) == 0
			&& (i == 0 || buffer[i - 1] == '\n'))
		{
			i += 2;
			if (sys->object_count >= MAX_OBJECTS)
				error_exit("Too many objects.\n", sys);
		obj = &sys->obj_list[sys->object_count++];
		obj->type = PLANE;
		obj->flags = OBJ_VISIBLE | OBJ_CASTS_SHADOW;
		phong_to_material(&obj->material);
			i += parse_xyz(buffer + i, &obj->plane.location, POINT, sys);
			i += parse_xyz(buffer + i, &obj->plane.rotation, VECTOR, sys);
			normalize_or_error(&obj->plane.rotation, sys);
			i += parse_rgb(buffer + i, &obj->material.color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
}