/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:10 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/01 12:04:10 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_int(char *in, int *value, t_system *sys)
{
	int		i;
	int		num;

	i = skip_spaces(in);
	num = ft_atoi(in + i);
	if (num < 0 || num > 255)
		error_exit("RGB value must be between 0 and 255\n", sys);
	*value = num;
	while (in[i] == '-' || in[i] == '+' || ft_isdigit(in[i]))
		i++;
	return (i);
}

int	parse_fov(char *in, int *value, t_system *sys)
{
	int		i;
	int		num;

	i = skip_spaces(in);
	num = ft_atoi(in + i);
	if (num < 0 || num > 180)
		error_exit("FOV must be between 0 and 180 degrees\n", sys);
	if (num == 0)
		num = 1;
	if (num == 180)
		num = 179;
	*value = num;
	while (in[i] == '-' || in[i] == '+' || ft_isdigit(in[i]))
		i++;
	return (i);
}

int	parse_float(char *in, float *out, t_float_check check, t_system *sys)
{
	int		i;

	i = skip_spaces(in);
	*out = ft_atof(in + i);
	if (*out < -FLOAT_MAX || *out > FLOAT_MAX)
		error_exit("Float overflow\n", sys);
	if (check == POSITIVE && *out < 0.0f)
		error_exit("Value must be positive\n", sys);
	else if (check == RATIO_0_1 && (*out < 0.0f || *out > 1.0f))
		error_exit("Value must be between 0 and 1\n", sys);
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
	i += parse_int(buffer + i, &r, sys);
	i += skip_commas(buffer + i, sys);
	i += parse_int(buffer + i, &g, sys);
	i += skip_commas(buffer + i, sys);
	i += parse_int(buffer + i, &b, sys);
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
	i += parse_float(buffer + i, &tuple->x, ANY, sys);
	i += skip_commas(buffer + i, sys);
	i += parse_float(buffer + i, &tuple->y, ANY, sys);
	i += skip_commas(buffer + i, sys);
	i += parse_float(buffer + i, &tuple->z, ANY, sys);
	tuple->w = w;
	return (i);
}
