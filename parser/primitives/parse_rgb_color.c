/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:54:06 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:06 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	parse_rgb_color(char *buffer, t_tuple *color, t_system *sys)
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
