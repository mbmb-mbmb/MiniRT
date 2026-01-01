/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:29 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/01 12:17:18 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	normalize_or_error(t_tuple *vec, t_system *sys)
{
	float	len;

	len = magnitude_vector(vec);
	if (len < EPSILON)
	{
		error_exit("Vector is a zero vector\n", sys);
		return ;
	}
	if (fabsf(len - 1.0f) > 0.01f)
	{
		printf("Warning: vector not normalized (len=%.3f), normalizing...\n", len);
		*vec = normalize_vector(vec);
	}
}

static void	check_ambient_light(char *buffer, t_system *sys)
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
			i += parse_float(buffer + i, &sys->amb_light.range, 0.0, 1.0, sys);
			i += parse_rgb(buffer + i, &sys->amb_light.color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
	if (a_found == 0)
		error_exit("No ambient light (A) found.\n", sys);
}

static void	check_camera(char *buffer, t_system *sys)
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

static void	check_lights(char *buffer, t_system *sys)
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
		if (ft_strncmp(buffer + i, "sp", 2) == 0 && (i == 0 || buffer[i - 1] == '\n'))
		{
			i += 2;
			if (sys->object_count >= MAX_OBJECTS)
				error_exit("Too many objects.\n", sys);
			obj = &sys->obj_list[sys->object_count++];
			obj->type = SPHERE;
			phong_to_material(&obj->material);
			i += parse_xyz(buffer + i, &obj->sphere.location, POINT, sys);
			i += parse_float(buffer + i, &obj->sphere.radius, 0.0f, FLOAT_MAX, sys);
			i += parse_rgb(buffer + i, &obj->material.color, sys);
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
		if (ft_strncmp(buffer + i, "cy", 2) == 0 && (i == 0 || buffer[i - 1] == '\n'))
		{
			i += 2;
			if (sys->object_count >= MAX_OBJECTS)
				error_exit("Too many objects.\n", sys);
			obj = &sys->obj_list[sys->object_count++];
			obj->type = CYLINDER;
			phong_to_material(&obj->material);
			i += parse_xyz(buffer + i, &obj->cylinder.location, POINT, sys);
			i += parse_xyz(buffer + i, &obj->cylinder.rotation, VECTOR, sys);
			normalize_or_error(&obj->cylinder.rotation, sys);
			i += parse_float(buffer + i, &obj->cylinder.diameter, 0.0f, FLOAT_MAX, sys);
			i += parse_float(buffer + i, &obj->cylinder.length, 0.0f, FLOAT_MAX, sys);
			i += parse_rgb(buffer + i, &obj->material.color, sys);
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
		if (ft_strncmp(buffer + i, "pl", 2) == 0 && (i == 0 || buffer[i - 1] == '\n'))
		{
			i += 2;
			if (sys->object_count >= MAX_OBJECTS)
				error_exit("Too many objects.\n", sys);
			obj = &sys->obj_list[sys->object_count++];
			obj->type = PLANE;
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

void	rt_parser(char *input, t_system *sys)
{
	int		fd;
	char	buffer[4096];
	int		bytes_read;
	char	buffer_overflow;

	if (!check_extension(input))
		error_exit("File must have .rt extension\n", sys);
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error_exit("Cannot open file\n", sys);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (read(fd, &buffer_overflow, 1) > 0)
		error_exit("File is too large\n", sys);
	if (bytes_read < 0)
		error_exit("Cannot read file\n", sys);
	buffer[bytes_read] = '\0';
	close(fd);
	check_ambient_light(buffer, sys);
	check_camera(buffer, sys);
	sys->light_count = 0;
	check_lights(buffer, sys);
	sys->object_count = 0;
	check_sphere(buffer, sys);
	check_cylinder(buffer, sys);
	check_plane(buffer, sys);
	ft_putstr_fd("Inputfile OK!\n", 1);
}
