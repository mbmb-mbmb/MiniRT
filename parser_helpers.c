#include "minirt.h"

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

int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 3, ".rt", 3) == 0);
}
