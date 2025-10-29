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
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
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
	while (buffer[i] && (ft_isdigit(buffer[i]) || buffer[i] == '.')) 
		i++;
	return (i);
}

static uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a);
}

static int	to_eightbit(char *in, int *value)
{
	int	i;
	int	num;

	i = 0;
	if (!ft_isdigit(in[i]))
		error_parser("RGB: expected digit\n");
	while (in[i] && ft_isdigit(in[i]))
		i++;
	num = ft_atoi(in);
	if (num < 0 || num > 255)
		error_parser("RGB: values should be between 0 and 255\n");
	*value = num;
	return (i);
}

static int	parse_rgb(char *buffer, t_data *data, int i)
{
	int	r;
	int	g;
	int	b;

	i += skip_spaces(buffer + i);
	i += to_eightbit(buffer + i, &r);
	i += skip_commas(buffer + i);
	i += skip_spaces(buffer + i);
	i += to_eightbit(buffer + i, &g);
	i += skip_commas(buffer + i);
	i += skip_spaces(buffer + i);
	i += to_eightbit(buffer + i, &b);
	data->amb_light.rgb = pack_rgba((uint8_t)r,(uint8_t) g,(uint8_t) b, 255);
	return (i);
}

static void	check_A(char *buffer, t_data *data)
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
			i += skip_spaces(buffer + i);
			data->amb_light.range = atof(buffer + i); //ft_atof tai to_double löytyykö Jyryltä?
			i += skip_float(buffer + i);
			i += parse_rgb(buffer, data, i);
		}
		i++;
	}
	if (A_found == 0)
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

void	rt_parser(char *input, t_data *data)
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
	check_A(buffer, data);
	ft_putstr_fd("Inputfile OK!\n", 1);
}
