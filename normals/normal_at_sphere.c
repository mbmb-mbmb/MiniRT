/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:59 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:20:44 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	normal_at_sphere(t_sphere *sphere, t_tuple *world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;
	t_tuple	origin;
	t_mat	transposed_inverse;

	object_point = transform_tuple_by_matrix(&sphere->inv_transform_to_obj,
			world_point);
	origin = create_point(0, 0, 0);
	object_normal = subtract_tuple(&object_point, &origin);
	transposed_inverse = transpose_matrix(&sphere->inv_transform_to_obj, 4);
	world_normal = transform_tuple_by_matrix(&transposed_inverse,
			&object_normal);
	world_normal.w = VECTOR;
	return (normalize_vector(&world_normal));
}
