/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:59 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:20:44 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	normal_at_cylinder(t_cylinder *cylinder, t_tuple *world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;
	t_mat	transposed_inverse;

	object_point = transform_tuple_by_matrix(&cylinder->inv_transform_to_obj,
			world_point);
	if (fabsf(object_point.y - 1.0f) < EPSILON)
		object_normal = create_vector(0, 1, 0);
	else if (fabsf(object_point.y + 1.0f) < EPSILON)
		object_normal = create_vector(0, -1, 0);
	else
		object_normal = create_vector(object_point.x, 0, object_point.z);
	transposed_inverse = transpose_matrix(&cylinder->inv_transform_to_obj, 4);
	world_normal = transform_tuple_by_matrix(&transposed_inverse,
			&object_normal);
	world_normal.w = VECTOR;
	return (normalize_vector(&world_normal));
}
