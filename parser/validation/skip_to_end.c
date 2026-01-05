#include "../../minirt.h"

int	skip_to_end(char *buffer, t_system *sys)
{
	int	i;

	i = skip_spaces(buffer);
	if (buffer[i] == '\n')
	{
		i++;
		return (i);
	}
	if (buffer[i] == '\0')
		return (i);
	error_exit("Some strange characters found around end of file.\n", sys);
	return (i);
}
