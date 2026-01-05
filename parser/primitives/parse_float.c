#include "../../minirt.h"

int	parse_float(char *in, float *out, t_float_check check, t_system *sys)
{
	int	i;

	i = skip_spaces(in);
	*out = ft_atof(in + i);
	if (*out < -FLOAT_MAX || *out > FLOAT_MAX)
		error_exit("Float overflow\n", sys);
	if (check == POSITIVE && *out < 0.0f)
		error_exit("Diameter and height must be positive.\n", sys);
	else if (check == RATIO_0_1 && (*out < 0.0f || *out > 1.0f))
		error_exit("Ratios must be between 0.0 and 1.0\n", sys);
	i += skip_float(in + i);
	return (i);
}
