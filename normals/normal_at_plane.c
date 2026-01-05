/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:59 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:20:44 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	normal_at_plane(t_plane *plane)
{
	t_tuple	local_normal;
	t_tuple	world_normal;
	t_mat	transposed_inverse;

	local_normal = create_vector(0, 1, 0);
	transposed_inverse = transpose_matrix(&plane->inv_transform_to_obj, 4);
	world_normal = transform_tuple_by_matrix(&transposed_inverse,
			&local_normal);
	world_normal.w = VECTOR;
	return (normalize_vector(&world_normal));
}
