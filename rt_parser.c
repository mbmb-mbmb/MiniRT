#include "minirt.h"

static void	error_parser(char *print, t_system *sys)
{
	ft_putstr_fd("Error\n", 2);
	if (print != NULL)
		ft_putstr_fd(print, 2);
	else
		ft_putstr_fd("TODO: General instructions for input format here\n", 2);
	sys->exit_code = 1;
	sys->state |= SHOULD_EXIT;
	exit(sys->exit_code);
}

static int	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] == '\t'))
		i++;
	return (i);
}

static int	skip_commas(char *buffer, t_system *sys)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != ',' && buffer[i] != '\n')
		i++;
	if (buffer[i] != ',')
		error_parser("Expected comma between componenets\n", sys);
	return (i + 1);
}

static int	skip_float(char *buffer)
{
	int	i;

	i = 0;
	if (buffer[i] == '-' || buffer[i] == '+')
		i++;
	while (buffer[i] && (ft_isdigit(buffer[i]) || buffer[i] == '.'))
		i++;
	return (i);
}

static int skip_to_end(char *buffer, t_system *sys)
{
	int i;

	i = skip_spaces(buffer);
	if (buffer[i] == '\n')
	{
		i++;
		return (i);
	}
	if (buffer[i] == '\0')
		return (i);
	error_parser("some strange characters found around end of file\n", sys);
	return (i);
}

static int	parse_int(char *in, int *value, int min, int max, t_system *sys)
{
	int		i;
	int		num;

	i = skip_spaces(in);
	num = ft_atoi(in + i);
	if (num < min || num > max)
		error_parser("Integer out of range\n", sys);
	*value = num;
	while (in[i] == '-' || in[i] == '+' || ft_isdigit(in[i]))
		i++;
	return (i);
}

static int	parse_float(char *in, float *out, float min, float max, t_system *sys)
{
	int		i;
	float	num;

	i = skip_spaces(in);
	num = atof(in + i); //FT_ATOI?
	if (num < min || num > max)
		error_parser("float out of range\n", sys);
	*out = num;
	i += skip_float(in + i);
	return (i);
}

uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a);
}

static int	parse_rgb(char *buffer, t_tuple *color, t_system *sys)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	i += parse_int(buffer + i, &r, 0, 255, sys);
	i += skip_commas(buffer + i, sys);
	i += parse_int(buffer + i, &g, 0, 255, sys);
	i += skip_commas(buffer + i, sys);
	i += parse_int(buffer + i, &b, 0, 255, sys);
	color->x = (float)r / 255.0f;
	color->y = (float)g / 255.0f;
	color->z = (float)b / 255.0f;
	color->w = 1.0f;
	return (i);
}

static int	parse_xyz(char *buffer, t_tuple *tuple, float w, t_system *sys)
{
	int	i;

	i = 0;
	i += parse_float(buffer + i, &tuple->x, -FLOAT_MAX, FLOAT_MAX, sys);
	i += skip_commas(buffer + i, sys);
	i += parse_float(buffer + i, &tuple->y, -FLOAT_MAX, FLOAT_MAX, sys);
	i += skip_commas(buffer + i, sys);
	i += parse_float(buffer + i, &tuple->z, -FLOAT_MAX, FLOAT_MAX, sys);
	tuple->w = w;
	return (i);
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

static int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 3, ".rt", 3) == 0);
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
