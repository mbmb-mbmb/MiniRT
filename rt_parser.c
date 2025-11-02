#include "minirt.h"

static void	error_parser(char *print)
{
	ft_putstr_fd("Error\n", 2);
	if(print != NULL)
		ft_putstr_fd(print, 2);
	else
		ft_putstr_fd("TODO: Instructions for input format here\n", 2);
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
	while (buffer[i] && buffer[i] != ',')
		i++;
	i++;
	return (i);
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
	error_parser("some rubbish characters found at end of file\n");
	return (i);
}

static int	parse_int(char *in, int *value, int min, int max)
{
	int	i;
	int	int_start;
	int	num;

	i = 0;
	i += skip_spaces(in + i);
	if (in[i] == '-' || in[i] == '+')
		i++;
	if (!ft_isdigit(in[i]))
		error_parser("Expected digit\n");
	int_start = i;
	while (in[i] && ft_isdigit(in[i]))
		i++;
	num = ft_atoi(in + int_start);  // Parse from start
	if (num < min || num > max)
		error_parser("Integer out of range\n");
	*value = num;
	return (i);
}

static int	parse_float(char *in, float *out, float min, float max)
{
	int		i;
	int		float_start;
	float	num;
	
	i = 0;
	i += skip_spaces(in + i);
	float_start = i;
	i += skip_float(in + i);
	num = atof(in + float_start); //ft_atof??
	if (num < min || num > max)
		error_parser("float out of range\n");
	*out = num;
	return (i);
}

static uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a);
}


static int	parse_rgb(char *buffer, t_system *sys, int i)
{
	int	r;
	int	g;
	int	b;


	i += parse_int(buffer + i, &r, 0, 255);
	i += skip_commas(buffer + i);
	i += parse_int(buffer + i, &g, 0, 255);
	i += skip_commas(buffer + i);
	i += parse_int(buffer + i, &b, 0, 255);
	sys->amb_light.rgb = pack_rgba((uint8_t)r,(uint8_t) g,(uint8_t) b, 255);
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

static void	check_A(char *buffer, t_system *sys)
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
			i = parse_rgb(buffer, sys, i);
			i += skip_to_end(buffer + i);
			continue ;
		}
		i++;
	}
	if (A_found == 0)
	error_parser(NULL);
}

static void	check_C(char *buffer, t_system *sys)
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
			i += parse_xyz(buffer + i, &sys->camera.rotation, VECTOR); //no check for normalization yet.
			i += parse_int(buffer + i, &sys->camera.fov, 0, 180);
			i += skip_to_end(buffer + i);		
			continue ;
		}
		i++;
	}
	if (C_found == 0)
		error_parser(NULL);
}

static int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 3)
		return (0);
	return (ft_strncmp(filename + len - 3, ".rt", len) == 0);
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
	check_A(buffer, sys);
	check_C(buffer, sys);
	ft_putstr_fd("Inputfile OK!\n", 1);
}
