/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:05:52 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:40:07 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static t_tuple	compute_pixel_on_canvas(t_camera *camera, uint32_t x,
		uint32_t y)
{
	float	world_x;
	float	world_y;

	world_x = camera->canvas_dims.half_width - ((float)x + 0.5f)
		* camera->canvas_dims.pixel_size;
	world_y = camera->canvas_dims.half_height - ((float)y + 0.5f)
		* camera->canvas_dims.pixel_size;
	return (create_point(world_x, world_y, -1.0f));
}

t_ray	ray_for_pixel(t_camera *camera, uint32_t x, uint32_t y)
{
	t_ray	ray;
	t_tuple	pixel_on_canvas;
	t_tuple	pixel_in_world;
	t_tuple	direction;

	pixel_on_canvas = compute_pixel_on_canvas(camera, x, y);
	pixel_in_world = transform_tuple_by_matrix(&camera->inverse,
			&pixel_on_canvas);
	direction = subtract_tuple(&pixel_in_world, &camera->world_origin);
	ray.origin = camera->world_origin;
	ray.direction = normalize_vector(&direction);
	return (ray);
}
