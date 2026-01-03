/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:41 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:07:42 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180.0);
}

bool	is_float_zero(float f)
{
	return (fabsf(f) < EPSILON);
}

bool	is_float_equal(float a, float b)
{
	return (fabsf(a - b) < EPSILON);
}
