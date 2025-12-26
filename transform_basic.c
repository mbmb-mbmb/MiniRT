/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_basic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:40 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:41 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat	translation(float x, float y, float z)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[0][3] = x;
	mat.m[1][3] = y;
	mat.m[2][3] = z;
	return (mat);
}

t_mat	scaling(float x, float y, float z)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[0][0] = x;
	mat.m[1][1] = y;
	mat.m[2][2] = z;
	return (mat);
}

static t_tuple	pick_non_parallel_vector(t_tuple *axis)
{
	if (fabsf(axis->x) < 0.9f)
		return (create_vector(1, 0, 0));
	return (create_vector(0, 0, 1));
}

t_mat	rotation_from_axis(t_tuple *axis)
{
	t_tuple	up;
	t_tuple	arbitrary;
	t_tuple	right;
	t_tuple	forward;
	t_mat	rot;

	up = normalize_vector(axis);
	arbitrary = pick_non_parallel_vector(&up);
	right = cross_product_tuple(&arbitrary, &up);
	right = normalize_vector(&right);
	forward = cross_product_tuple(&up, &right);
	rot = create_identity_matrix(4);
	rot.m[0][0] = right.x;
	rot.m[1][0] = right.y;
	rot.m[2][0] = right.z;
	rot.m[0][1] = up.x;
	rot.m[1][1] = up.y;
	rot.m[2][1] = up.z;
	rot.m[0][2] = forward.x;
	rot.m[1][2] = forward.y;
	rot.m[2][2] = forward.z;
	return (rot);
}

t_mat	skew(float xy, float xz, float yx, float yz, float zx, float zy)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[0][1] = xy;
	mat.m[0][2] = xz;
	mat.m[1][0] = yx;
	mat.m[1][2] = yz;
	mat.m[2][0] = zx;
	mat.m[2][1] = zy;
	return (mat);
}

void	set_transform(t_object *obj, t_mat *transform)
{
	t_mat	inverse;

	if (obj->type == SPHERE)
	{
		obj->sphere.transform_to_world = *transform;
		inverse = invert_matrix(transform);
		obj->sphere.inv_transform_to_obj = inverse;
		obj->sphere.is_transformed = true;
	}
	else if (obj->type == PLANE)
	{
		obj->plane.transform_to_world = *transform;
		inverse = invert_matrix(transform);
		obj->plane.inv_transform_to_obj = inverse;
		obj->plane.is_transformed = true;
	}
	else if (obj->type == CYLINDER)
	{
		obj->cylinder.transform_to_world = *transform;
		inverse = invert_matrix(transform);
		obj->cylinder.inv_transform_to_obj = inverse;
		obj->cylinder.is_transformed = true;
	}
}
