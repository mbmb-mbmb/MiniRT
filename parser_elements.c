
# include "minirt.h"

void	check_ambient_light(char *buffer, t_system *sys)
{
	int	i;
	int	a_found;

	i = 0;
	a_found = 0;
	while (buffer[i])
	{
		if (buffer[i] == 'A' && (i == 0 || buffer[i - 1] == '\n'))
		{
			a_found++;
			i++;
			if (a_found > 1)
				error_exit("Only one ambient light (A) allowed.\n", sys);
			i += parse_float(buffer + i, &sys->amb_light.range, RATIO_0_1, sys);
			i += parse_rgb(buffer + i, &sys->amb_light.color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
	if (a_found == 0)
		error_exit("No ambient light (A) found.\n", sys);
}

void	check_camera(char *buffer, t_system *sys)
{
	int	i;
	int	c_found;

	i = 0;
	c_found = 0;
	while (buffer[i])
	{
		if (buffer[i] == 'C' && (i == 0 || buffer[i - 1] == '\n'))
		{
			c_found++;
			i++;
			if (c_found > 1)
				error_exit("Only one camera (C) allowed.\n", sys);
			i += parse_xyz(buffer + i, &sys->camera.location, POINT, sys);
			i += parse_xyz(buffer + i, &sys->camera.rotation, VECTOR, sys);
			normalize_or_error(&sys->camera.rotation, sys);
			i += parse_fov(buffer + i, &sys->camera.fov, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
	if (c_found == 0)
		error_exit("No camera (C) found.\n", sys);
}

void	check_lights(char *buffer, t_system *sys)
{
	int				i;
	t_spot_light	*light;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == 'L' && (i == 0 || buffer[i - 1] == '\n'))
		{
			i++;
			if (sys->light_count >= MAX_LIGHTS)
				error_exit("Too many lights.\n", sys);
			light = &sys->light_list[sys->light_count++];
			i += parse_xyz(buffer + i, &light->location, POINT, sys);
			i += parse_float(buffer + i, &light->range, RATIO_0_1, sys);
			i += parse_rgb(buffer + i, &light->color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
}

void	phong_to_material(t_material *material)
{
	material->ambient = MATERIAL_AMBIENT;
	material->diffuse = MATERIAL_DIFFUSE;
	material->specular = MATERIAL_SPECULAR;
	material->shininess = MATERIAL_SHININESS;
}
