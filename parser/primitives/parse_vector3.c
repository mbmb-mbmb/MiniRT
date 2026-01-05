/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:54:07 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:07 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	parse_vector3(char *buffer, t_tuple *tuple, float w, t_system *sys)
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
