#include "minirt.h"

static void	phong_to_material(t_material *material)
{
	material->ambient = MATERIAL_AMBIENT;
	material->diffuse = MATERIAL_DIFFUSE;
	material->specular = MATERIAL_SPECULAR;
	material->shininess = MATERIAL_SHININESS;
}

static void	check_AmbLight(char *buffer, t_system *sys)
{
	int	i;
	int	A_found;

	i = 0;
	A_found = 0;
	while (buffer[i])
	{
		if (buffer[i] == 'A' && (i == 0 || buffer[i-1] == '\n'))
		{
			A_found++;
			i++;
			if (A_found > 1)
				error_parser("Only one ambient light (A) allowed.\n", sys);
			i += parse_float(buffer + i, &sys->amb_light.range, 0.0, 1.0, sys);
			i += parse_rgb(buffer + i, &sys->amb_light.color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
	if (A_found == 0)
	error_parser(NULL, sys);
}

static void	check_camera(char *buffer, t_system *sys)
{
	int	i;
	int	C_found;

	i = 0;
	C_found = 0;
	while (buffer[i])
	{
		if (buffer[i] == 'C' && (i == 0 || buffer[i-1] == '\n'))
		{
			C_found++;
			i++;
			if (C_found > 1)
				error_parser("Only one camera (C) allowed.\n", sys);
			i += parse_xyz(buffer + i, &sys->camera.location, POINT, sys);
			i += parse_xyz(buffer + i, &sys->camera.rotation, VECTOR, sys);
			if (magnitude_vector(&sys->camera.rotation) > 1.0)
				error_parser("TODO: vector not normalized error", sys);
			i += parse_int(buffer + i, &sys->camera.fov, 0, 180, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
	if (C_found == 0)
		error_parser(NULL, sys);
}


static void	check_lights(char *buffer, t_system *sys)
{
	int				i;
	t_spot_light	*light;
	
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == 'L' && (i == 0 || buffer[i-1] == '\n'))
		{
			i++;
			if (sys->light_count >= MAX_LIGHTS)
				error_parser("Too many lights.\n", sys);
			light = &sys->light_list[sys->light_count++];
			i += parse_xyz(buffer + i, &light->location, POINT, sys);
			i += parse_float(buffer + i, &light->range, 0.0, 1.0, sys);
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

static void	check_sphere(char *buffer, t_system *sys)
{
	int				i;
	t_object		*obj;
	
	i = 0;
	while (buffer[i])
	{
		if (ft_strncmp(buffer + i, "sp", 2) == 0 && (i == 0 || buffer[i-1] == '\n'))
		{
			i += 2;
			if (sys->object_count >= MAX_OBJECTS)
				error_parser("Too many objects.\n", sys);
			obj = &sys->obj_list[sys->object_count++];
			obj->type = SPHERE;
			phong_to_material(&obj->sphere.material);
			i += parse_xyz(buffer + i, &obj->sphere.location, POINT, sys);
			i += parse_float(buffer + i, &obj->sphere.radius, -FLOAT_MAX, FLOAT_MAX, sys);
			i += parse_rgb(buffer + i, &obj->sphere.material.color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
}

static void	check_cylinder(char *buffer, t_system *sys)
{
	int			i;
	t_object	*obj;

	i = 0;
	while (buffer[i])
	{
		if (ft_strncmp(buffer + i, "cy", 2) == 0 && (i == 0 || buffer[i-1] == '\n'))
		{
			i += 2;
			if (sys->object_count >= MAX_OBJECTS)
				error_parser("Too many objects.\n", sys);
			obj = &sys->obj_list[sys->object_count++];
			obj->type = CYLINDER;
			phong_to_material(&obj->cylinder.material);
			i += parse_xyz(buffer + i, &obj->cylinder.location, POINT, sys);
			i += parse_xyz(buffer + i, &obj->cylinder.rotation, VECTOR, sys);
			if (magnitude_vector(&sys->camera.rotation) > 1.0)
				error_parser("TODO: vector not normalized error", sys);
			i += parse_float(buffer + i, &obj->cylinder.diameter, -FLOAT_MAX, FLOAT_MAX, sys);
			i += parse_float(buffer + i, &obj->cylinder.length, -FLOAT_MAX, FLOAT_MAX, sys);
			i += parse_rgb(buffer + i, &obj->cylinder.material.color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}

		i++;
	}
}

static void	check_plane(char *buffer, t_system *sys)
{
	int				i;
	t_object		*obj;

	i = 0;
	while (buffer[i])
	{
		if (ft_strncmp(buffer + i, "pl", 2) == 0 && (i == 0 || buffer[i-1] == '\n'))
		{
			i += 2;
			if (sys->object_count >= MAX_OBJECTS)
				error_parser("Too many objects.\n", sys);
			obj = &sys->obj_list[sys->object_count++];
			obj->type = PLANE;
			phong_to_material(&obj->plane.material);
			i += parse_xyz(buffer + i, &obj->plane.location, POINT, sys);
			i += parse_xyz(buffer + i, &obj->plane.rotation, VECTOR, sys);
			if (magnitude_vector(&sys->camera.rotation) > 1.0)
				error_parser("TODO: vector not normalized error", sys);
			i += parse_rgb(buffer + i, &obj->plane.material.color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
}

void	rt_parser(char *input, t_system *sys)
{
	int		fd;
	char	buffer[2096];
	int		bytes_read;
	char	buffer_overflow;

	if (!check_extension(input))
		error_parser("Error: File must have .rt extension\n", sys);
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error_parser("Error: Cannot open file\n", sys);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if(read(fd, &buffer_overflow, 1) > 0)
		error_parser("Error: File is too large\n", sys);
	buffer[bytes_read] = '\0';
	close(fd);
	check_AmbLight(buffer, sys);
	check_camera(buffer, sys);
	sys->light_count = 0;
	check_lights(buffer, sys);
	sys->object_count = 0;
	check_sphere(buffer, sys);
	check_cylinder(buffer, sys);
	check_plane(buffer, sys);
	ft_putstr_fd("Inputfile OK!\n", 1);
}
