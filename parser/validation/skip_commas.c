#include "../../minirt.h"

int	skip_commas(char *buffer, t_system *sys)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != ',' && buffer[i] != '\n')
		i++;
	if (buffer[i] != ',')
		error_exit("Expected comma between components.\n", sys);
	return (i + 1);
}
