/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:09:04 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:55:40 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tuple	normalize_vector(t_tuple *a)
{
	float	mag;
	t_tuple	v_result;
	int		ak;

	v_result = (t_tuple){};
	v_result.w = TUPLE_INCORRECT;
	ak = get_tuple_type(a);
	if (ak != VECTOR)
		return (v_result);
	mag = magnitude_vector(a);
	if (mag < EPSILON)
		return (v_result);
	v_result = (t_tuple){.x = a->x / mag, .y = a->y / mag, .z = a->z / mag,
		.w = VECTOR};
	return (v_result);
}
