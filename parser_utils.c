#include "minirt.h"

void	error_parser(char *print, t_system *sys)
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

int	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] == '\t'))
		i++;
	return (i);
}

int	skip_commas(char *buffer, t_system *sys)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != ',' && buffer[i] != '\n')
		i++;
	if (buffer[i] != ',')
		error_parser("Expected comma between componenets\n", sys);
	return (i + 1);
}

int	skip_float(char *buffer)
{
	int	i;

	i = 0;
	if (buffer[i] == '-' || buffer[i] == '+')
		i++;
	while (buffer[i] && (ft_isdigit(buffer[i]) || buffer[i] == '.'))
		i++;
	return (i);
}

int skip_to_end(char *buffer, t_system *sys)
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

int	parse_int(char *in, int *value, int min, int max, t_system *sys)
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

int	parse_float(char *in, float *out, float min, float max, t_system *sys)
{
	int		i;
	float	num;

	i = skip_spaces(in);
	num = atof(in + i);
	if (num < min || num > max)
		error_parser("float out of range\n", sys);
	*out = num;
	i += skip_float(in + i);
	return (i);
}

int	parse_rgb(char *buffer, t_tuple *color, t_system *sys)
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

int	parse_xyz(char *buffer, t_tuple *tuple, float w, t_system *sys)
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

int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 3, ".rt", 3) == 0);
}
