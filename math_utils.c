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

// float	radians_to_degrees(float radians)
// {
// 	return (radians * 180.0 / M_PI);
// }

bool	is_float_zero(float f)
{
	return (fabsf(f) < EPSILON);
}

bool	is_float_equal(float a, float b)
{
	return (fabsf(a - b) < EPSILON);
}

// bool	is_tuple_equal(const t_tuple *a, const t_tuple *b)
// {
// 	return (is_float_equal(a->w, b->w)
// 		&& is_float_equal(a->x, b->x)
// 		&& is_float_equal(a->z, b->z)
// 		&& is_float_equal(a->y, b->y));
// }
