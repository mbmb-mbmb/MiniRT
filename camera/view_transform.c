/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:05:52 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:40:07 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_mat	build_orientation_from_view(t_tuple *eye, t_tuple *target,
		t_tuple *up)
{
	t_tuple	forward;
	t_tuple	upn;
	t_tuple	left;
	t_tuple	true_up;
	t_mat	orientation;

	forward = subtract_tuple(target, eye);
	forward = normalize_vector(&forward);
	upn = normalize_vector(up);
	left = cross_product_tuple(&forward, &upn);
	true_up = cross_product_tuple(&left, &forward);
	orientation = create_identity_matrix(4);
	orientation.m[0][0] = left.x;
	orientation.m[0][1] = left.y;
	orientation.m[0][2] = left.z;
	orientation.m[1][0] = true_up.x;
	orientation.m[1][1] = true_up.y;
	orientation.m[1][2] = true_up.z;
	orientation.m[2][0] = -forward.x;
	orientation.m[2][1] = -forward.y;
	orientation.m[2][2] = -forward.z;
	set_matrix_dim(&orientation, 4);
	return (orientation);
}

t_mat	view_transform(t_tuple *eye, t_tuple *target, t_tuple *up)
{
	t_mat	orientation;
	t_mat	translate;

	orientation = build_orientation_from_view(eye, target, up);
	translate = translation(-eye->x, -eye->y, -eye->z);
	return (multiply_matrices(&orientation, &translate));
}
