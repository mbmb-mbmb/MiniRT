#include "minirt.h"

static void	error_parser(char *print)
{
	ft_putstr_fd("Error\n", 2);
	if(print != NULL)
		ft_putstr_fd(print, 2);
	else
		ft_putstr_fd("TODO: General instructions for input format here\n", 2);
	exit(1);
}

static int	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] == '\t'))
		i++;
	return (i);
}

static int	skip_commas(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != ',' && buffer[i] != '\n')
		i++;
	if (buffer[i] != ',')
		error_parser("Expected comma between componenets\n");
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

static int skip_to_end(char *buffer)
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
	error_parser("some strange characters found around end of file\n");
	return (i);
}

static int	parse_int(char *in, int *value, int min, int max)
{
	int		i;
	int		num;

	i = skip_spaces(in);
	num = ft_atoi(in + i);
	if (num < min || num > max)
		error_parser("Integer out of range\n");
	*value = num;
	while (in[i] == '-' || in[i] == '+' || ft_isdigit(in[i]))
		i++;
	return (i);
}

static int	parse_float(char *in, float *out, float min, float max)
{
	int		i;
	float	num;

	i = skip_spaces(in);
	num = atof(in + i); //FT_ATOI?
	if (num < min || num > max)
		error_parser("float out of range\n");
	*out = num;
	i += skip_float(in + i);
	return (i);
}

uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a);
}


static int	parse_rgb(char *buffer, uint32_t *color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	i += parse_int(buffer + i, &r, 0, 255);
	i += skip_commas(buffer + i);
	i += parse_int(buffer + i, &g, 0, 255);
	i += skip_commas(buffer + i);
	i += parse_int(buffer + i, &b, 0, 255);
	*color = pack_rgba((uint8_t)r,(uint8_t) g,(uint8_t) b, 255);
	return (i);
}

static int	parse_xyz(char *buffer, t_tuple *tuple, float w)
{
	int	i;

	i = 0;
	i += parse_float(buffer + i, &tuple->x, -FLOAT_MAX, FLOAT_MAX);
	i += skip_commas(buffer + i);
	i += parse_float(buffer + i, &tuple->y, -FLOAT_MAX, FLOAT_MAX);
	i += skip_commas(buffer + i);
	i += parse_float(buffer + i, &tuple->z, -FLOAT_MAX, FLOAT_MAX);
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
			if(A_found > 1)
				error_parser("Only one ambient light (A) allowed.\n");
			i += parse_float(buffer + i, &sys->amb_light.range, 0.0, 1.0);
			i += parse_rgb(buffer + i, &sys->amb_light.rgb);
			i += skip_to_end(buffer + i);
			continue ;
		}
		i++;
	}
	if (A_found == 0)
	error_parser(NULL);
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
			if(C_found > 1)
				error_parser("Only one camera (C) allowed.\n");
			i += parse_xyz(buffer + i, &sys->camera.location, POINT);
			i += parse_xyz(buffer + i, &sys->camera.rotation, VECTOR);
			if (magnitude_tuple(&sys->camera.rotation) > 1.0)
				error_parser("TODO: vector not normalized error");
			i += parse_int(buffer + i, &sys->camera.fov, 0, 180);
			i += skip_to_end(buffer + i);
			continue ;
		}
		i++;
	}
	if (C_found == 0)
		error_parser(NULL);
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
				error_parser("Too many lights.\n");
			light = &sys->light_list[sys->light_count++];
			i += parse_xyz(buffer + i, &light->location, POINT);
			i += parse_float(buffer + i, &light->range, 0.0, 1.0);
			i += parse_rgb(buffer + i, &light->color);
			i += skip_to_end(buffer + i);
			continue ;
		}
		i++;
	}
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
				error_parser("Too many objects.\n");
			obj = &sys->obj_list[sys->object_count++];
			obj->type = SPHERE;
			obj->sphere.transform = create_identity_matrix(4);
			obj->sphere.inv_transform = create_identity_matrix(4);
			obj->sphere.is_transformed = false;
			i += parse_xyz(buffer + i, &obj->sphere.location, POINT);
			i += parse_float(buffer + i, &obj->sphere.radius, -FLOAT_MAX, FLOAT_MAX);
			i += parse_rgb(buffer + i, &obj->sphere.color);
			i += skip_to_end(buffer + i);
			continue ;
		}
		i++;
	}
}

static void	check_cylinder(char *buffer, t_system *sys)
{
	int				i;
	t_object		*obj;

	i = 0;
	while (buffer[i])
	{
		if (ft_strncmp(buffer + i, "cy", 2) == 0 && (i == 0 || buffer[i-1] == '\n'))
		{
			i += 2;
			if (sys->object_count >= MAX_OBJECTS)
			error_parser("Too many objects.\n");
			obj = &sys->obj_list[sys->object_count++];
			obj->type = CYLINDER;
			i += parse_xyz(buffer + i, &obj->cylinder.location, POINT);
			i += parse_xyz(buffer + i, &obj->cylinder.rotation, VECTOR);
			if (magnitude_tuple(&sys->camera.rotation) > 1.0)
				error_parser("TODO: vector not normalized error");
			i += parse_float(buffer + i, &obj->cylinder.diameter, -FLOAT_MAX, FLOAT_MAX);
			i += parse_float(buffer + i, &obj->cylinder.length, -FLOAT_MAX, FLOAT_MAX);
			i += parse_rgb(buffer + i, &obj->cylinder.color);
			i += skip_to_end(buffer + i);
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
			error_parser("Too many objects.\n");
			obj = &sys->obj_list[sys->object_count++];
			obj->type = PLANE;
			i += parse_xyz(buffer + i, &obj->plane.location, POINT);
			i += parse_xyz(buffer + i, &obj->plane.rotation, VECTOR);
			if (magnitude_tuple(&sys->camera.rotation) > 1.0)
				error_parser("TODO: vector not normalized error");
			i += parse_rgb(buffer + i, &obj->plane.color);
			i += skip_to_end(buffer + i);
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

	if (!check_extension(input))
		error_parser("Error: File must have .rt extension\n");
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error_parser("Error: Cannot open file\n");
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	check_AmbLight(buffer, sys);
	check_camera(buffer, sys);
	check_lights(buffer, sys);
	sys->object_count = 0;
	check_sphere(buffer, sys);
	check_cylinder(buffer, sys);
	check_plane(buffer, sys);
	ft_putstr_fd("Inputfile OK!\n", 1);
}
