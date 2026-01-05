#include "../../minirt.h"

void	check_ambient_light(char *buffer, t_system *sys)
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
			i += parse_float(buffer + i, &sys->amb_light.range, RATIO_0_1, sys);
			i += parse_rgb_color(buffer + i, &sys->amb_light.color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
	if (a_found == 0)
		error_exit("No ambient light (A) found.\n", sys);
}
