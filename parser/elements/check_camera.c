#include "../../minirt.h"

void	check_camera(char *buffer, t_system *sys)
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
			i += parse_vector3(buffer + i, &sys->camera.location, POINT, sys);
			i += parse_vector3(buffer + i, &sys->camera.rotation, VECTOR, sys);
			validate_and_normalize_direction(&sys->camera.rotation, sys);
			i += parse_fov(buffer + i, &sys->camera.fov, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
	if (c_found == 0)
		error_exit("No camera (C) found.\n", sys);
}
