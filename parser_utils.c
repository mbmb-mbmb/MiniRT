/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:10 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:11 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	parse_int(char *in, int *value, int min, int max, t_system *sys)
{
	int		i;
	int		num;

	i = skip_spaces(in);
	num = ft_atoi(in + i);
	if (num < min || num > max)
		error_parser("Integer out of range\n", sys);
	if (num == 0)
		num = 1;
	if (num == 180)
		num = 179;
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
	num = ft_atof(in + i);
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


